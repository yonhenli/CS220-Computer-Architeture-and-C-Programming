#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/wait.h>
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/stat.h>  

#define SHELL_CMD_MAX_COUNT        10
#define SHELL_CMD_MAX_LENGTH       20
#define SHELL_IN_OUT_FILE_MAX_SIZE 20
#define SHELL_BUFFER               64
#define SHELL_PIPE_MAX_COUNT       10
#define SHELL_PIPE_READ_WRITE      2

typedef struct command
{
  char *arg[SHELL_CMD_MAX_LENGTH];
  char *input_file;
  char *output_file;
} cmd_t;

static int shell_parse_cmd_line(char *data, cmd_t *cmd)
{
  int i = 0;

  cmd->input_file = NULL;
  cmd->output_file = NULL;

  char *token = strtok(data, " ");

  while(token)
  {
    /* parse redirecting output */
    if(*token == '>')
    {
      /* check if there is no space after > */
      if(*(token + 1))
      {
        cmd->output_file = token + 1;
      }
      else
      {
        cmd->output_file = strtok(NULL, " \t\r\n\a");
      }

    }
    /* parse redirecting input */
    else if(*token == '<')
    {
      if(*(token + 1))
      {
        cmd->input_file = token + 1;
      }
      else
      {
        cmd->input_file = strtok(NULL, " \t\r\n\a");
      }

    }
    else
    {
      /* the easiest case */
      cmd->arg[i++] = token;

    }
    token = strtok(NULL, " ");
  }

  cmd->arg[i] = NULL;

  return 0;
}

static int shell_parse_pipe(char *data, cmd_t cmd[])
{
  int count = 0;
  char *temp;
  char *token = strtok_r(data, "|",  &temp);

  while(token)
  {
    shell_parse_cmd_line(token, &cmd[count++]);
    token = strtok_r(NULL, "|", &temp);
  }

  return count;
}

int shell_cd_command(char *command, char *path)
{
  int return_value = 0;

  if(strncmp(command, "cd", 2) == 0)
    if((return_value = chdir(path)) < 0)
    {
      perror("chdir");
    }
  return return_value;
}

static void shell_process(void)
{
  char cmd_buf[SHELL_BUFFER], pathname[SHELL_BUFFER];
  cmd_t cmds[SHELL_CMD_MAX_COUNT];
  pid_t pid;
  int fd_in, fd_out, pipe_num, pipe_fd[SHELL_PIPE_MAX_COUNT][SHELL_PIPE_READ_WRITE], cmd_num = 0;
  int i = 0, j = 0;

  while(1)
  {
    printf("hello!!>");

    /* get input */
    memset(cmd_buf, 0, sizeof(cmd_buf));
    fgets(cmd_buf, sizeof(cmd_buf), stdin);
    if(strcmp(cmd_buf, "exit\n") == 0) break;

    /* add null terminator to the line */
    for(i = 0; i< strlen(cmd_buf); i++) {
      if(cmd_buf[i] == '\n') cmd_buf[i] = '\0';
    }

    /* cmd_buf[strlen(cmd_buf) - 1] = '\0'; */

    cmd_num = shell_parse_pipe(cmd_buf, cmds);

    shell_cd_command(cmds[0].arg[0], cmds[0].arg[1]);

    pipe_num = cmd_num - 1;
    if(pipe_num > SHELL_PIPE_MAX_COUNT)
    {
      continue;
    }
    /* create n pipes */
    for(i = 0; i < pipe_num; ++i)
    {
      pipe(pipe_fd[i]);
    }

    /* create pipe_num+1 processes, including 1 parent process and pipe_num child processes */
    for(i = 0; i < cmd_num; ++i)
    {
      if((pid = fork()) < 0)
      {
        printf("fork fail!\n");
        exit(1);
      }
      if(pid == 0)
      {
        /* if it is a child process, go to the next step */
        break;
      }
    }

    /* child process */
    if(pid == 0)
    {
      /* if there is an input file */
      if(cmds[i].input_file)
      {
        if((fd_in = open(cmds[i].input_file, O_RDONLY)) < 0)
        {
          perror("open fail!\n");
        }
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
      }

      /* if there is an output file */
      if(cmds[i].output_file)
      {
        if((fd_out = open(cmds[i].output_file,  O_RDWR | O_CREAT, S_IRUSR | S_IWUSR), 0644) < 0)
        {
          perror("open fail!\n");
        }
        dup2(fd_out, STDOUT_FILENO);
        close(fd_out);
      }
      
      /* manage pipe */
      if(pipe_num)
      {
        /* the first process: open write & close read */
        if(0 == i)
        {
          close(pipe_fd[i][0]);
          dup2(pipe_fd[i][1], STDOUT_FILENO);
          close(pipe_fd[i][1]);

          /* close other pipes */
          for(j = 1; j < pipe_num; ++j)
          {
            close(pipe_fd[j][0]);
            close(pipe_fd[j][1]);
          }
        }

        /* the last process: close write & open read */
        else if(pipe_num == i)
        {
          close(pipe_fd[i - 1][0]);
          dup2(pipe_fd[i - 1][0], STDIN_FILENO);
          close(pipe_fd[i - 1][0]);
          
          /* close other pipes */
          for(j = 0; j < pipe_num - 1; ++j)
          {
            close(pipe_fd[j][0]);
            close(pipe_fd[j][1]);
          }
        }

        /* 1~pipe_num-1, */
        else
        {
          dup2(pipe_fd[i - 1][0], STDIN_FILENO);
          close(pipe_fd[i - 1][0]);

          dup2(pipe_fd[i][1], STDOUT_FILENO);
          close(pipe_fd[i][1]);

          for(j = 0; j < pipe_num; ++j)
          {
            if((j != i - 1) || j != i)
            {
              close(pipe_fd[j][0]);
              close(pipe_fd[j][1]);
            }
          }
        }
      }

      execvp(cmds[i].arg[0], cmds[i].arg);
    }

    /* parent */
    else
    {
      for(i = 0; i < pipe_num; ++i)
      {
        close(pipe_fd[i][0]);
        close(pipe_fd[i][1]);
      }
      for(i = 0; i < cmd_num; ++i)
      {
        wait(NULL);
      }
    }
  }
}

int main(int argc, char **argv)
{
  shell_process();

  return 0;
}
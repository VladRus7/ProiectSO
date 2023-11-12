/*
Prima parte a problemei
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/stat.h>


void citire_header(const char *fisier, int *inaltime, int *latime, struct stat *st_file) {

int file = open(fisier, O_RDONLY);
    if (file == -1) {
        printf("Eroare la deschiderea fisierului");
        exit(-1);
    }
    
    lseek(file, 18, SEEK_SET);
    read(file, latime, sizeof(int));
    read(file, inaltime, sizeof(int));

    fstat(file, st_file);

    close(file);
    
    
}

void scrie_statistica(const char *fisier, int inaltime, int latime, struct stat *st_file) {
    int file = open("statistica.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file== -1) {
        printf("Eroare la deschiderea fisierului de iesire");
        exit(-1);
    }

    char buffer[500];
    struct tm *time_info;
    time_info = localtime(&(st_file->st_mtime));

    sprintf(buffer, "nume fisier: %s\n", fisier);
    write(file, buffer, strlen(buffer));

    sprintf(buffer, "inaltime: %d\n", inaltime);
    write(file, buffer, strlen(buffer));

    sprintf(buffer, "lungime: %d\n", latime);
    write(file, buffer, strlen(buffer));

    sprintf(buffer, "dimensiune: %ld\n", st_file->st_size);
    write(file, buffer, strlen(buffer));

    sprintf(buffer, "identificatorul utilizatorului: %d\n", st_file->st_uid);
    write(file, buffer, strlen(buffer));

    strftime(buffer, sizeof(buffer), "timpul ultimei modificari: %d.%m.%Y %H:%M:%S\n", time_info);
    write(file, buffer, strlen(buffer));

    sprintf(buffer, "contorul de legaturi: %ld\n", st_file->st_nlink);
    write(file, buffer, strlen(buffer));

    sprintf(buffer, "drepturi de acces user: %c%c%c\n",
            (st_file->st_mode & S_IRUSR) ? 'R' : '-',
            (st_file->st_mode & S_IWUSR) ? 'W' : '-',
            (st_file->st_mode & S_IXUSR) ? 'X' : '-');
    write(file, buffer, strlen(buffer));

    sprintf(buffer, "drepturi de acces grup: %c%c%c\n",
            (st_file->st_mode & S_IRGRP) ? 'R' : '-',
            (st_file->st_mode & S_IWGRP) ? 'W' : '-',
            (st_file->st_mode & S_IXGRP) ? 'X' : '-');
    write(file, buffer, strlen(buffer));

    sprintf(buffer, "drepturi de acces altii: %c%c%c\n",
            (st_file->st_mode & S_IROTH) ? 'R' : '-',
            (st_file->st_mode & S_IWOTH) ? 'W' : '-',
            (st_file->st_mode & S_IXOTH) ? 'X' : '-');
    write(file, buffer, strlen(buffer));

    close(file);
}

int main(int argc, char *argv[])
{
   if(argc != 2){
       printf("Usage: %s <fisier_intrare>\n", argv[0]);
       exit(-1);
   } 
   int inaltime, latime;
    struct stat st_file;
    
    citire_header(argv[1], &inaltime, &latime, &st_file);
    scrie_statistica(argv[1], inaltime, latime, &st_file);
   
  

    return 0;
}
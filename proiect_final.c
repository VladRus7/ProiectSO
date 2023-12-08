#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <stdint.h>
#include <math.h>
#define PATH_MAX 4096

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

void scrie_statistica_bmp(const char *fisier, int inaltime, int latime, struct stat *st_file) {
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

void scrie_statistica(const char *fisier, struct stat *st_file) {
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

void scrie_statistica_leg(const char *leg,char *dest, struct stat *st_file) {
   int file = open("statistica.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file== -1) {
        printf("Eroare la deschiderea fisierului de iesire");
        exit(-1);
    }

    char buffer[500];
 

    sprintf(buffer, "nume legatura: %s\n", leg);
    write(file, buffer, strlen(buffer));


    sprintf(buffer, "dimensiune legatura: %ld\n", st_file->st_size);
    write(file, buffer, strlen(buffer));

    sprintf(buffer, "dimensiune fisier target: %ld\n", strlen(dest));
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

void scrie_statistica_dir(const char *dir, struct stat *st_file) {
   int file = open("statistica.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file== -1) {
        printf("Eroare la deschiderea fisierului de iesire");
        exit(-1);
    }

    char buffer[500];
 

    sprintf(buffer, "nume director: %s\n", dir);
    write(file, buffer, strlen(buffer));


    sprintf(buffer, "identificatorul utilizatorului: %d\n", st_file->st_uid);
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

void parcurge_director(const char *director) {
    DIR *dir = opendir(director);
    if (dir == NULL) {
        printf("Eroare la deschiderea directorului \n");
        exit(-1);
    }

    struct dirent *entry;
    char cale[PATH_MAX];
    int inaltime, latime;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            sprintf(cale, "%s/%s", director, entry->d_name);
            struct stat st;
            if (lstat(cale, &st) == -1) {
                printf("Eroare la obtinerea informatiilor despre %s", entry->d_name);
                continue;
            }

            if (S_ISDIR(st.st_mode)) {
             
                scrie_statistica_dir(entry->d_name, &st);
            } else if (S_ISREG(st.st_mode)) {
                if (strstr(entry->d_name, ".bmp") != NULL) {
                    citire_header(cale, &inaltime, &latime, NULL);
                    scrie_statistica_bmp(entry->d_name,inaltime,latime,  &st);
                } else {
                    scrie_statistica(entry->d_name, &st);
                }
            } else if (S_ISLNK(st.st_mode)) {
                char dest[PATH_MAX];
                ssize_t len = readlink(cale, dest, sizeof(dest) - 1);
                if (len != -1) {
                    dest[len] = '\0';
                    scrie_statistica_leg(entry->d_name, dest, &st);
                } else {
                    printf("Eroare la citirea link-ului simbolic %s", entry->d_name);
                }
            }
          
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <director_intrare> <director_iesire>\n", argv[0]);
        exit(-1);
    }

    parcurge_director(argv[1]);

    return 0;
}
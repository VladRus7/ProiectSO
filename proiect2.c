/*
A doua parte a problemei
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
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

void scrie_statistica(const char *nume, struct stat *st) {
    printf("nume fisier: %s\n", nume);
    printf("dimensiune: %ld\n", st->st_size);
    printf("identificatorul utilizatorului: %d\n", st->st_uid);
    printf("contorul de legaturi: %ld\n", st->st_nlink);
    printf("drepturi de acces user: %c%c%c\n",
           (st->st_mode & S_IRUSR) ? 'R' : '-',
           (st->st_mode & S_IWUSR) ? 'W' : '-',
           (st->st_mode & S_IXUSR) ? 'X' : '-');
          
    printf("drepturi de acces grup: %c%c%c\n",
           (st->st_mode & S_IRGRP) ? 'R' : '-',
           (st->st_mode & S_IWGRP) ? 'W' : '-',
           (st->st_mode & S_IXGRP) ? 'X' : '-');

    printf("drepturi de acces altii: %c%c%c\n",
           (st->st_mode & S_IROTH) ? 'R' : '-',
           (st->st_mode & S_IWOTH) ? 'W' : '-',
           (st->st_mode & S_IXOTH) ? 'X' : '-');
           
}

void parcurge_director(const char *director) {
    DIR *dir = opendir(director);
    if (dir == NULL) {
        printf("Eroare la deschiderea directorului");
        exit(-1);
    }

    struct dirent *entry;
    char cale[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            sprintf(cale, "%s/%s", director, entry->d_name);

            struct stat st;
            if (lstat(cale, &st) == -1) {
                printf("Eroare la obtinerea informatiilor despre %s", entry->d_name);
                continue;
            }

            if (S_ISDIR(st.st_mode)) {
                printf("nume director: %s\n", entry->d_name);
                scrie_statistica(entry->d_name, &st);
            } else if (S_ISREG(st.st_mode)) {
                if (strstr(entry->d_name, ".bmp") != NULL) {
                    citire_header(cale, NULL, NULL, NULL);
                    scrie_statistica(entry->d_name, &st);
                } else {
                    scrie_statistica(entry->d_name, &st);
                }
            } else if (S_ISLNK(st.st_mode)) {
                char dest[PATH_MAX];
                ssize_t len = readlink(cale, dest, sizeof(dest) - 1);
                if (len != -1) {
                    dest[len] = '\0';
                    printf("nume legatura: %s\n", entry->d_name);
                    printf("dimensiune legatura: %ld\n", st.st_size);
                    printf("dimensiune fisier destinatie: %ld\n", strlen(dest));
                    scrie_statistica(entry->d_name, &st);
                } else {
                    printf("Eroare la citirea link-ului simbolic %s", entry->d_name);
                }
            }
            // Alte tipuri de intrări nu vor fi tratate
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <director_intrare>\n", argv[0]);
        exit(-1);
    }

    parcurge_director(argv[1]);

    return 0;
}
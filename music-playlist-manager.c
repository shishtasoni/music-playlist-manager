#include <stdio.h>
#include <string.h>

#define MAX 100

char titles[MAX][50];
char artists[MAX][50];
int durations[MAX];
int count = 0;

int queue[MAX];
int front = 0, rear = -1;

int history[MAX];
int top = -1;

void addSong() {
    if (count == MAX) {
        printf("Playlist full\n");
        return;
    }
    printf("Enter title: ");
    scanf(" %[^\n]", titles[count]);
    printf("Enter artist: ");
    scanf(" %[^\n]", artists[count]);
    printf("Enter duration (seconds): ");
    scanf("%d", &durations[count]);
    count++;
    printf("Song added\n");
}

void displayPlaylist() {
    int i;
    if (count == 0) {
        printf("Playlist is empty\n");
        return;
    }
    printf("\n%-5s %-25s %-20s %s\n", "No.", "Title", "Artist", "Duration(s)");
    for (i = 0; i < count; i++) {
        printf("%-5d %-25s %-20s %d\n", i + 1, titles[i], artists[i], durations[i]);
    }
}

void searchSong() {
    char name[50];
    int i;
    printf("Enter title to search: ");
    scanf(" %[^\n]", name);
    for (i = 0; i < count; i++) {
        if (strcmp(titles[i], name) == 0) {
            printf("Found at position %d\n", i + 1);
            printf("Title: %s | Artist: %s | Duration: %d sec\n",
                   titles[i], artists[i], durations[i]);
            return;
        }
    }
    printf("Song not found\n");
}

void deleteSong() {
    char name[50];
    int i, pos = -1;
    printf("Enter title to delete: ");
    scanf(" %[^\n]", name);
    for (i = 0; i < count; i++) {
        if (strcmp(titles[i], name) == 0) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("Song not found\n");
        return;
    }
    for (i = pos; i < count - 1; i++) {
        strcpy(titles[i], titles[i + 1]);
        strcpy(artists[i], artists[i + 1]);
        durations[i] = durations[i + 1];
    }
    count--;

    /* song numbers shifted, so clear queue and history */
    front = 0;
    rear = -1;
    top = -1;
    printf("Song deleted (play queue and history were cleared)\n");
}

void addToQueue() {
    int n;
    if (count == 0) {
        printf("Playlist is empty\n");
        return;
    }
    displayPlaylist();
    printf("Enter song number to queue: ");
    scanf("%d", &n);
    if (n < 1 || n > count) {
        printf("Invalid song number\n");
        return;
    }
    if (rear == MAX - 1) {
        printf("Queue full\n");
        return;
    }
    rear++;
    queue[rear] = n - 1;
    printf("%s added to queue\n", titles[n - 1]);
}

void playNext() {
    int s;
    if (front > rear) {
        printf("Queue empty\n");
        return;
    }
    s = queue[front];
    front++;
    printf("Now playing: %s by %s\n", titles[s], artists[s]);
    top++;
    history[top] = s;
}

void showHistory() {
    int i;
    if (top == -1) {
        printf("No songs played yet\n");
        return;
    }
    printf("Recently played (latest first):\n");
    for (i = top; i >= 0; i--) {
        printf("%s by %s\n", titles[history[i]], artists[history[i]]);
    }
}

int main() {
    int choice;
    do {
        printf("\n===== MUSIC PLAYLIST MANAGER =====\n");
        printf("1. Add song\n");
        printf("2. Delete song\n");
        printf("3. Search song\n");
        printf("4. Display playlist\n");
        printf("5. Add song to play queue\n");
        printf("6. Play next song\n");
        printf("7. Show play history\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addSong(); break;
            case 2: deleteSong(); break;
            case 3: searchSong(); break;
            case 4: displayPlaylist(); break;
            case 5: addToQueue(); break;
            case 6: playNext(); break;
            case 7: showHistory(); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice\n");
        }
    } while (choice != 0);

    return 0;
}
#include <glut.h>
#include <windows.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include <mmsystem.h>
#pragma warning(suppress : 4996);
#define max 60
#define _CRT_SECURE_NO_WARNINGS
#define columns 40
#define rows 40
#define FPS 10
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
int snakelen = 5;
int score = 0;
int* sc = &score;
int gridx = 40, gridy = 40;
int foodx, foody;
void drawgrid();
void drawsnake();
void initgrid();
void unit();
void drawfood();
int random();
void keyboard_callback(int, int, int);
int gameover = 0;
int food = 1;

struct players
{
    char name[20];
    int scores;
} name_score[100];

void display()
{
    FILE* f2, * f3;
    glClear(GL_COLOR_BUFFER_BIT);
    drawgrid();
    drawsnake();
    drawfood();
    glutSwapBuffers();
    struct players player = { 0 };


    char str[20];
    if (gameover == 1) {
        PlaySound(TEXT("bubbles.wav"), NULL, SND_ASYNC);
        //char str = score + '0';
        //char* message_text;
        //message_text = "your score is : " + score;
        //MessageBox(0, str, L"GAMEOVER", 0);
        // char length_string[20];
        // _snprintf_s(length_string, 20, "%ld", score);
        MessageBox(0, L"you lost", L"GAMEOVER", 0);
        printf("your score= %d", *sc);
        player.scores = score;
        f2 = fopen("names.txt", "a");
        if (f2 == NULL) { printf("file error");return; }
        fprintf(f2, "  score = %d\n", player.scores);
        fclose(f2);
        exit(0);

    }


}
void drawfood()
{
    if (food == 1)
        random(foodx, foody);
    food = 0;
    glColor3f(0.1, 1, 0.8);
    glRectf(foodx, foody, foodx + 1, foody + 1);

}
int random()
{
    int maxX = gridx - 2;
    int minX = 1;
    int maxY = gridy - 2;
    int minY = 1;
    srand(time(NULL));
    foodx = minX + rand() % (maxX - minX);
    foody = minY + rand() % (maxY - minY);
}
void reshape(int width, int height)
{
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, columns, 0, rows, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
void myInit()
{
    glClearColor(1, 1, 0.9, 1);
    initgrid(columns, rows);
}
void initgrid(int x, int y)
{

    gridx = x;
    gridy = y;
}
void drawgrid()
{
    for (int x = 0; x < 40; x++)
    {
        for (int y = 0; y < 40; y++)
        {
            unit(x, y);
        }
    }
}
void unit(int W, int H)
{
    if (W == 0 || H == 0 || H == 39 || W == 39)
    {
        glLineWidth(3.0);
        glColor3f(1, 0.6, 1);
    }
    else
    {
        glLineWidth(1.0);
        glColor3f(1, 0.8, 0.3);
    }
    glBegin(GL_LINE_LOOP);
    glVertex2f(W, H);
    glVertex2f(W + 1, H);
    glVertex2f(W + 1, H + 1);
    glVertex2f(W, H + 1);
    glEnd();
}
void timer_callback()
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 10, timer_callback, 0);
}
extern short sDirection;
short sDirection = RIGHT;

void keyboard_callback(int key, int salma, int omar)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (sDirection != DOWN)
            sDirection = UP;
        break;
    case GLUT_KEY_DOWN:
        if (sDirection != UP)
            sDirection = DOWN;
        break;
    case GLUT_KEY_LEFT:
        if (sDirection != RIGHT)
            sDirection = LEFT;
        break;
    case GLUT_KEY_RIGHT:
        if (sDirection != LEFT)
            sDirection = RIGHT;
        break;
    }
}
int posx[60] = { 20,20,20,20,20 }, posy[60] = { 20,19,18,17,16 };
void drawsnake()
{
    for (int i = snakelen - 1;i > 0;i--)
    {
        posx[i] = posx[i - 1];
        posy[i] = posy[i - 1];
    }
    if (sDirection == UP)
        posy[0]++;
    else if (sDirection == DOWN)
        posy[0]--;
    else if (sDirection == LEFT)
        posx[0]--;
    else if (sDirection == RIGHT)
        posx[0]++;
    for (int i = 0;i < snakelen;i++) {
        if (i == 0)
            glColor3f(0.9, 0.5, 0.5);
        else
            glColor3f(1, 0.8, 0.9);
        glRectd(posx[i], posy[i], posx[i] + 1, posy[i] + 1);
    }


    if (posx[0] == 0 || posx[0] == 40 - 1 || posy[0] == 0 || posy[0] == 40 - 1) {
        gameover = 1;
    }
    if (posx[0] == foodx && posy[0] == foody) {
        PlaySound(TEXT("eat.wav"), NULL, SND_ASYNC);
        snakelen++;
        if (snakelen > max)
            snakelen = max;
        food = 1;
        score = score + 10;


    }

}

int sound() {
    PlaySound(TEXT("music.wav"), NULL, SND_LOOP | SND_ASYNC);
}

void sort_file()
{
    int size = 0;
    FILE* f3;
    f3 = fopen("names.txt", "r");

    if (f3 == NULL)
    {
        printf("error");
        return 0;
    }
    while (!feof(f3))
    {
        char ch;
        char str1[100], str2[100];
        fscanf(f3, "%s %s %s %ch", str1, name_score[size].name, str2, &ch);
        fscanf(f3, "%d", &name_score[size].scores);
        size++;
    }
    for (int i = 1; i < size; ++i)
    {
        for (int j = 0; j < size - i; j++)
        {
            if (name_score[j + 1].scores > name_score[j].scores)
            {
                struct players temp;

                temp.scores = name_score[j].scores;
                name_score[j].scores = name_score[j + 1].scores;
                name_score[j + 1].scores = temp.scores;
                strcpy(temp.name, name_score[j].name);
                strcpy(name_score[j].name, name_score[j + 1].name);
                strcpy(name_score[j + 1].name, temp.name);
            }
        }
    }
    fclose(f3);
    f3 = fopen("name.txt", "w");
    for (int i = 0;i < size;i++)
    {
        fprintf(f3, "Player %s score: %d \n",name_score[i].name,name_score[i].scores );
    }
    fclose(f3);
}

int main(int argc, char* argv[])
{

    sound();
    struct players player = { 0 };
    struct players temp;
    MessageBox(0, L"press enter to enter your name", L"ENTER NAME", 0);
    printf("enter  ");
    scanf("%s", player.name);
    FILE* f1, * f3;
    f1 = fopen("names.txt", "a");
    if (f1 == NULL) { printf("file error");return; }
    fprintf(f1, "player %s  ", player.name);
    sort_file();
    fclose(f1);
    int x = 20, y = 20;
    glutInit(&argc, argv);
    glutInitWindowPosition(200, 150);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutCreateWindow("SNAKE");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer_callback, 0);
    glutSpecialFunc(keyboard_callback);
    myInit();
    initgrid(x, y);
    drawgrid();
    


    glutMainLoop();



    return 0;

}

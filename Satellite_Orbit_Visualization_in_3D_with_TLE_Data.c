#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "orekit_headers.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Define satellite data struct
typedef struct {
    char* name;
    char* line1;
    char* line2;
    float color[3];
} SatelliteData;

SatelliteData* satelliteDataList;
int numSatellites;

void readTLEData(const char* tleFile) {
    FILE* file = fopen(tleFile, "r");
    if (file == NULL) {
        printf("Failed to open TLE file.\n");
        exit(1);
    }

    // Count the number of satellite records
    char ch;
    numSatellites = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            numSatellites++;
        }
    }
    rewind(file);

    // Read the satellite records
    satelliteDataList = (SatelliteData*)malloc(numSatellites * sizeof(SatelliteData));
    for (int i = 0; i < numSatellites; i++) {
        SatelliteData* satelliteData = &satelliteDataList[i];

        // Read the name
        size_t nameSize = 0;
        getline(&satelliteData->name, &nameSize, file);
        satelliteData->name[strcspn(satelliteData->name, "\n")] = '\0';

        // Read line 1
        size_t line1Size = 0;
        getline(&satelliteData->line1, &line1Size, file);
        satelliteData->line1[strcspn(satelliteData->line1, "\n")] = '\0';

        // Read line 2
        size_t line2Size = 0;
        getline(&satelliteData->line2, &line2Size, file);
        satelliteData->line2[strcspn(satelliteData->line2, "\n")] = '\0';

        // Set default color to black
        satelliteData->color[0] = 0.0f;
        satelliteData->color[1] = 0.0f;
        satelliteData->color[2] = 0.0f;
    }

    fclose(file);
}

void drawSphere(GLfloat radius, GLint slices, GLint stacks) {
    GLUquadricObj* quadric = gluNewQuadric();
    gluSphere(quadric, radius, slices, stacks);
    gluDeleteQuadric(quadric);
}

void drawCylinder(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks) {
    GLUquadricObj* quadric = gluNewQuadric();
    gluCylinder(quadric, base, top, height, slices, stacks);
    gluDeleteQuadric(quadric);
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Draw Earth
    glColor3f(0.0f, 0.0f, 1.0f);
    drawSphere(1.0f, 32, 32);

    // Draw satellite paths
    for (int i = 0; i < numSatellites; i++) {
        SatelliteData* satelliteData = &satelliteDataList[i];
        glColor3fv(satelliteData->color);

        TLE* tle = orekit_tle_create("", satelliteData->line1, satelliteData->line2);
        Orbit* orbit = orekit_tle_get_orbit(tle);
        double t = 0.0;
        double dt = 5.0;
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < 72; j++) {
            AbsoluteDate* date = orekit_absolute_date_create_from_j2000_epoch_shifted_by(t);
            PVCoordinates* pvCoordinates = orekit_orbit_get_pv_coordinates(orbit, date);
            double x = orekit_pv_coordinates_get_position_x(pvCoordinates) / 1000.0;
            double y = orekit_pv_coordinates_get_position_y(pvCoordinates) / 1000.0;
            double z = orekit_pv_coordinates_get_position_z(pvCoordinates) / 1000.0;
            glVertex3d(x, y, z);
            t += dt;

            // Cleanup
            orekit_pv_coordinates_free(pvCoordinates);
            orekit_absolute_date_free(date);
        }
        glEnd();

        // Cleanup
        orekit_orbit_free(orbit);
        orekit_tle_free(tle);
    }

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

int main(int argc, char** argv) {
    // Initialize Orekit
    orekit_init();

    // Read TLE data from a file
    const char* tleFile = "tle_data.txt";  // Path to the TLE file
    readTLEData(tleFile);

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Satellite Orbits");

    // Set GLUT callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);

    // Initialize OpenGL
    initGL();

    // Start the main GLUT loop
    glutMainLoop();

    // Cleanup
    for (int i = 0; i < numSatellites; i++) {
        free(satelliteDataList[i].name);
        free(satelliteDataList[i].line1);
        free(satelliteDataList[i].line2);
    }
    free(satelliteDataList);

    // Shut down Orekit
    orekit_shutdown();

    return 0;
}


#include "RayTracing.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>

enum SceneTypes
{
	DIM,
	BG,
	GLOB,
	SPHERE,
	SOURCE,
	UNDEFINED,
};

SceneTypes str2scene_types(string s)
{
#define IF_RETURN(pattern, TYPE) if( s == pattern) return TYPE;
	IF_RETURN("dimensions", DIM);
	IF_RETURN("background", BG);
	IF_RETURN("global", GLOB);
	IF_RETURN("sphere", SPHERE);
	IF_RETURN("source", SOURCE);
	return UNDEFINED;
}

using namespace std;

//Funkcja pobiera informacje z pliku
void ReadSceneFromFile(string fileName);

int     im_size = 400;
bool	fast = true;
float   windowObserverDim = 20.0;

Point3D   startingPoint;						//punkt, z ktorego wychodzi promien
Vector3D   startingDir = { 0.0, 0.0, -1.0 };	//wektor opisujacy kierunek promienia

RayTracing rayTracing;

//Funkcja inicjalizujaca definiujaca sposob rzutowania
void Myinit(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-windowObserverDim / 2, windowObserverDim / 2, -windowObserverDim / 2, windowObserverDim / 2, -windowObserverDim / 2, windowObserverDim / 2);
	glMatrixMode(GL_MODELVIEW);
}

//Funkcja rysujaca obraz oswietlonej sceny
void RenderScene(void)
{
	clock_t time = clock();
	int all = 0;           //pozycja rysowanego piksela "calkowitoliczbowa"
	float x_fl, y_fl;    //pozycja rysowanego piksela "zmiennoprzecinkowa"
	int im_size_2;       //polowa rozmiaru obrazu w pikselach
	int lastPrintLength = 0;

	im_size_2 = im_size / 2;    //obliczenie polowy rozmiaru obrazu w pikselach
	const int iterations = (im_size_2 << 1) * (im_size_2 << 1);
	glClear(GL_COLOR_BUFFER_BIT);
	//Rysowanie - przekatna w prawo i w dol
	for (int y = im_size_2; y > -im_size_2; y--)
	{
		for (int x = -im_size_2; x < im_size_2; x++, all++)
		{
			// auto now = clock();
			// if ((now - time) / ((double)CLOCKS_PER_SEC) > 0.5)
			// {
			// 	stringstream ss;
			// 	ss << (all / (double)iterations) * 100.0 << "%";
			// 	cout << "\r";
			// 	for (int i = 0; i < lastPrintLength; ++i)
			// 		cout << " ";
			// 	auto s = ss.str();
			// 	lastPrintLength = s.length();
			// 	cout << "\r" << s;
			// 	glFlush();
			// 	time = now;
			// }

			// cout << "( "<<x << ", "<<y<<")\n";

			x_fl = (float)x / (im_size / windowObserverDim);
			y_fl = (float)y / (im_size / windowObserverDim);

			//przeliczenie pozycji(x,y) w pikselach na pozycje
			//"zmiennoprzecinkowa" w oknie obserwatora
			startingPoint[0] = x_fl;
			startingPoint[1] = y_fl;
			startingPoint[2] = windowObserverDim;

			//wyznaczenie poczatku sledzonego promienia dla rysowanego piksela
			ColorRGB color;
			color[0] = 0.0;
			color[1] = 0.0;
			color[2] = 0.0;

			color = rayTracing.TraceFast(startingPoint, startingDir);

			glBegin(GL_POINTS);
			glColor3f(color[0], color[1], color[2]);
			glVertex2f(x_fl, y_fl);
			glEnd();
		}
	}
	glutSwapBuffers();
}

void ReadSceneFromFile(string fileName)
{
	string buffer = "";
	float value = 0.0;
	int i = 0;

	fstream file(fileName.c_str(), ios::in);
	if (!file.is_open()){
		cout << "Blad otworzenia pliku ze scena (" << fileName << ")" << endl;
		system("PAUSE");
	}
	Sphere custom_sphere;
	Light source;
	ColorRGB color;
	while (!file.eof()) {
		file >> buffer;
		cout << buffer << endl;
		switch (str2scene_types(buffer))
		{
		case DIM:
			file >> im_size;
			break;
		case BG:
			file >> flow(color, >> );
			rayTracing.setBackgroundColor(color);
			break;
		case GLOB:
			file >> flow(color, >> );
			cout << flow(color, <<" "<<)<<endl;
			rayTracing.setGlobalAmbient(color);
			break;
		case SPHERE:
			file >> custom_sphere;
			rayTracing.addSolid(new Sphere( custom_sphere ));
			break;
		case SOURCE:
			file >> source;
			rayTracing.addLight(source);
			break;
		case UNDEFINED:
			break;
		}
	}
	file.close();
}

void keys(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '1':rayTracing.maxSteps = 1;
        break;
        case '2':rayTracing.maxSteps = 2;
        break;
        case '3':rayTracing.maxSteps = 3;
        break;
        case '4':rayTracing.maxSteps = 5;
        break;
        case '5':rayTracing.maxSteps = 10;
        break;
    }
    cout << "\r";
    cout << rayTracing.maxSteps;
    
}

void idle()
{
	rayTracing.solids[0]->rotateX(0.1);
	rayTracing.solids[1]->rotateX(0.1);

	// cout << flow(spheres[0].position, <<", " <<) << endl;

	for( int i = 2; i < rayTracing.solids.size(); ++i)
		rayTracing.solids[i]->rotateZ(-0.05);
	RenderScene();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	// if (argc > 1)
	// {
	// 	cout << "no elo";
	// 	rayTracing.maxSteps = atoi(argv[1]);
	// }
	ReadSceneFromFile("scena.txt");
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(im_size, im_size);
	glutCreateWindow("RayTracing");
    glutKeyboardFunc(keys);
	glutIdleFunc(idle);
	Myinit();
	glutDisplayFunc(RenderScene);
	rayTracing.print();
	glutMainLoop();

	return 0;
}
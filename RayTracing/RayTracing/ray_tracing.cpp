
#include "Sphere.hpp"
#include "Light.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "ColorRGB.hpp"
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

//Funkcja wyznacza wspolrzedne punktu przeciecia promienia z obiektem
int Intersect(Point3D p, Point3D v);

//Funkcja oblicza kolor piksela dla promienia zaczynajacego sie w punkcie p i biegnacego w kierunku wskazywanym przez wektor v
void Trace(Point3D p, Vector3D v, int step);

//Funkcja oblicza kierunek odbicia promienia w punkcie
void Reflect(Vector3D v);

//Funkcja pobiera informacje z pliku
void ReadSceneFromFile(string fileName);


int     im_size = 400;
bool	fast = true;
float   windowObserverDim = 20.0;

vector<Sphere> spheres;
vector<Light> lights;

//Parametry swiatla rozproszonego
ColorRGB   global_ambient;

//Parametry sledzonego promienia
Point3D   startingPoint;						//punkt, z ktorego wychodzi promien
Vector3D   startingDir = { 0.0, 0.0, -1.0 };	//wektor opisujacy kierunek promienia

//Wektor normalny do powierzchni
Vector3D   normalVector;
Vector3D   reflectionVector;

//Zmienne pomocnicze
Point3D	intersPoint;		//wspolrzedne (x,y,z) punktu przeciecia promienia i sfery
Point3D intersColor;		//skladowe coloru dla oswietlonego punktu na powierzchni sfery
ColorRGB	color;
Point3D backcolor;			//kolor tla wczytywany z pliku
GLubyte pixel[1][1][3];		//skladowe koloru rysowanego piksela

int     number = 10;

int		maxSteps = 5;			//limit iteracji

//Funkcja wyznacza wspolrzedne punktu przeciecia promienia z obiektem
inline float sq(float a)
{
	return a*a;
}

int Intersect(Point3D p, Vector3D v) {
	float r, a, b, c, d;
	float distance = 1000000000000;
	int status = -1;
	for (unsigned i = 0; i < spheres.size(); i++) {
		a = sq(v[0]) + sq(v[1]) + sq(v[2]);
		b = 2 * (v[0] * (p[0] - spheres[i].position[0])
			+ v[1] * (p[1] - spheres[i].position[1])
			+ v[2] * (p[2] - spheres[i].position[2]));
		c = sq(p[0]) + sq(p[1]) + sq(p[2])
			- 2 * (spheres[i].position[0] * p[0]
			+ spheres[i].position[1] * p[1]
			+ spheres[i].position[2] * p[2])
			+ sq(spheres[i].position[0])
			+ sq(spheres[i].position[1])
			+ sq(spheres[i].position[2])
			- sq(spheres[i].radius);
		d = b*b - 4 * a*c;
		if (d >= 0)
		{
			r = (-b - sqrt(d)) / (2 * a);
			if (r > 0 && r < distance)
			{
				intersPoint[0] = p[0] + r*v[0];
				intersPoint[1] = p[1] + r*v[1];
				intersPoint[2] = p[2] + r*v[2];
				distance = sqrt(sq(intersPoint[0] - p[0]) +
					sq(intersPoint[1] - p[1]) +
					sq(intersPoint[2] - p[2])
					);
				status = i;
			}
		}
	}
	return status;
}

//Funkcja oblicza kolor piksela dla promienia zaczynajacego sie w punkcie p i biegnacego w kierunku wskazywanym przez wektor v
void Trace(Point3D p, Vector3D v, int step)
{
	if (step > maxSteps)
		return;

	number = Intersect(p, v);
	if (number >= 0) {
		auto normal = spheres[number].getNormalVector(intersPoint);
		//Normal(number);
		Reflect(normal);
		auto x=spheres[number].phong(v, lights, intersPoint, global_ambient);
		color[0] += x[0];
		color[1] += x[1];
		color[2] += x[2];
		Trace(intersPoint, reflectionVector, step + 1);
	}
	else
		return;
}

//Funkcja oblicza kierunek odbicia promienia w punkcie
void Reflect(Vector3D v) {
	float	n_dot_i;
	Vector3D   invert = { -v[0], -v[1], -v[2] };

	invert.normalize();

	n_dot_i = Vector3D::scalarMul(invert, normalVector);
	reflectionVector[0] = 2 * (n_dot_i)*normalVector[0] - invert[0];
	reflectionVector[1] = 2 * (n_dot_i)*normalVector[1] - invert[1];
	reflectionVector[2] = 2 * (n_dot_i)*normalVector[2] - invert[2];

	reflectionVector.normalize();
	//Normalization(reflectionVector);
}

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
	glFlush();

	ofstream ofs("log.txt", ios_base::out | ios_base::trunc);

	//Rysowanie - przekatna w prawo i w dol
	for (int y = im_size_2; y > -im_size_2; y--)
	{
		for (int x = -im_size_2; x < im_size_2; x++, all++)
		{
			auto now = clock();
			if ((now - time) / ((double)CLOCKS_PER_SEC) > 0.5)
			{
				stringstream ss;
				ss << (all / (double)iterations) * 100.0 << "%";
				cout << "\r";
				for (int i = 0; i < lastPrintLength; ++i)
					cout << " ";
				auto s = ss.str();
				lastPrintLength = s.length();
				cout << "\r" << s;
				glFlush();
				time = now;
			}

			x_fl = (float)x / (im_size / windowObserverDim);
			y_fl = (float)y / (im_size / windowObserverDim);

			//przeliczenie pozycji(x,y) w pikselach na pozycje
			//"zmiennoprzecinkowa" w oknie obserwatora
			startingPoint[0] = x_fl;
			startingPoint[1] = y_fl;
			startingPoint[2] = windowObserverDim;

			//wyznaczenie poczatku sledzonego promienia dla rysowanego piksela
			color[0] = 0.0;
			color[1] = 0.0;
			color[2] = 0.0;

			if (x_fl > 0.0 && y_fl < 5.0)
				cout << "";

			//wyznaczenie coloru piksela
			Trace(startingPoint, startingDir, 1);

			//if (color[0] == 0.0) color[0] = backcolor[0];
			//if (color[1] == 0.0) color[1] = backcolor[1];
			//if (color[2] == 0.0) color[2] = backcolor[2];

			if (fast)
			{
				if (color[0] != 0.0 && color[1] != 0.0 && color[2] != 0.0)
				{
					ofs << y_fl << ": "
						<< color[0] << ", "
						<< color[1] << ", "
						<< color[2] << "\n";
				}

				glBegin(GL_POINTS);
				glColor3f(color[0], color[1], color[2]);
				glVertex2f(x_fl, y_fl);
				glEnd();
			}
			else
			{
				//konwersja wartosci wyliczonego oswietlenia na liczby od 0 do 255
				color[0] > 1 ? pixel[0][0][0] = 255 : pixel[0][0][0] = color[0] * 255;
				color[1] > 1 ? pixel[0][0][1] = 255 : pixel[0][0][1] = color[1] * 255;
				color[2] > 1 ? pixel[0][0][2] = 255 : pixel[0][0][2] = color[2] * 255;

				glRasterPos3f(x_fl, y_fl, 0);
				//inkrementacja pozycji rastrowej dla rysowania piksela

				glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
				//Narysowanie kolejnego piksela na ekranie
			}
		}
	}
	ofs.close();
	cout << "\r";
	for (int i = 0; i < lastPrintLength; ++i)
		cout << " ";
	cout << "\r";
	glFlush();
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
	while (!file.eof()) {
		file >> buffer;
		cout << buffer << endl;
		switch (str2scene_types(buffer))
		{
		case DIM:
			file >> im_size;
			cout << im_size;
			break;
		case BG:
			file >> flow(backcolor, >> );
			cout << flow(backcolor, << ", " << );
			break;
		case GLOB:
			file >> flow(global_ambient, >> );
			cout << flow(global_ambient, << ", " << );
			break;
		case SPHERE:
			file >> custom_sphere;
			cout << custom_sphere;
			spheres.push_back(custom_sphere);
			break;
		case SOURCE:
			file >> source;
			cout << source;
			lights.push_back(source);
			break;
		case UNDEFINED:
			break;
		}
	}
	file.close();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	ReadSceneFromFile("scena.txt");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(im_size, im_size);
	glutCreateWindow("RayTracing");
	Myinit();
	glutDisplayFunc(RenderScene);
	glutMainLoop();

	return 0;
}
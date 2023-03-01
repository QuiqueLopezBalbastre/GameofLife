/*
Juego de la Vida

	Argumento 1'0: Regla de supervivencia
		- Hasta 3 dígitos
		- Cada dígito significa que la célula solo sobrevive si se encuentra al lado de x nº de células
	Argumento 1'5: Regla de nacimiento
		- Hasta 2 dígitos
		- Cada dígito significa que la célula solo nace si se encuentra al lado de x nº de células
	Argumento 2: Nº total de células por línea
*/

#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/time.h>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



unsigned char fps=25;
double current_time,last_time;

int total_cells = 0, cellperrow = 0, counter = 0;
float cell_size = 0.0f;

bool *cells, *nextgen;
int *survivalcondition, birthcondition;

void DivideNumbers(char* str){
	if(strlen(str) == 4){
		survivalcondition = (int *)calloc(2, sizeof(int));
		*(survivalcondition + 0) = (int) *(str + 0) - 48;
		*(survivalcondition + 1) = (int) *(str + 1) - 48;
		birthcondition = (int) *(str + 3) - 48;
	}else if(strlen(str) == 3){
		survivalcondition = (int*)calloc(1,sizeof(int));
		*(survivalcondition + 0) = (int) *(str + 0) - 48;
		birthcondition = (int)*(str + 2) - 48;
	}else{
		printf("Faltan condiciones de supervivencia o nacimiento");
	}
}


void InitCells(){
	cells = (bool *)calloc(total_cells, sizeof(bool));
	nextgen = (bool *)calloc(total_cells, sizeof(bool));
	for(int i = 0; i < total_cells; i++){
		*(cells + i) = rand()%2;
		/*if(*(cells + i) == 0){
			printf("\nCelula %d: Muerta", i);
		}else{
			printf("\nCelula %d: Viva", i);
		}*/
	}
}

int CountCells(int position){
	int cell = 0, counter = 0, modulo, division;
	esat::Vec2 cellcheck;
	modulo = position % cellperrow;
	division = position / cellperrow;
	if(position / cellperrow == 0){
		// Central izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Central derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Inferior izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Inferior central
		cellcheck.x = modulo;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Inferior derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	}else if(position / cellperrow == cellperrow){
		// Superior izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Superior central
		cellcheck.x = modulo;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Superior derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Central izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Central derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	}else if(position % cellperrow == 0){
		// Superior central
		cellcheck.x = modulo;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Superior derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Central derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Inferior central
		cellcheck.x = modulo;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Inferior derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		return counter;
	}else if(position % cellperrow == cellperrow){
		// Superior izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Superior central
		cellcheck.x = modulo;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Central izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Inferior izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
		// Inferior central
		cellcheck.x = modulo;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	}else{
	//Superior izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if(*(cells + cell)){
			counter++;
		}
	// Superior central
		cellcheck.x = modulo;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	// Superior derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division - 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	// Central izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	// Central derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	// Inferior izquierda
		cellcheck.x = modulo - 1;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	// Inferior central
		cellcheck.x = modulo;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	// Inferior derecha
		cellcheck.x = modulo + 1;
		cellcheck.y = division + 1;
		cell = cellcheck.y * cellperrow + cellcheck.x;
		if (*(cells + cell))
		{
			counter++;
		}
	}
	return counter;
}

void UpdateCell(bool *celd, bool *next, int offset){
	counter = CountCells(offset);
	//printf("\nCell %d tiene %d al lado", offset, counter);
	if((*celd) && (counter != *(survivalcondition + 0) && counter != *(survivalcondition + 1))){
		(*next) = false;
	}
	if(!(*celd) && counter == birthcondition){
		(*next) = true;
	}
}


void DrawDungeon(){
	esat::DrawSetStrokeColor(0,255,255);
	for(int i = 0; i <= cellperrow; i++){
		for(int j = 0; j <= cellperrow; j++){
			esat::DrawLine(i * cell_size, 0, i * cell_size, 800);
			esat::DrawLine(0, j * cell_size, 800, j * cell_size);
		}
	}
}

void DrawSquare(int position){
	esat::Vec2 *pointer = nullptr;
	esat::Vec2 cellorigin = {0.0f,0.0f};
	pointer = (esat::Vec2*) calloc (4, sizeof(esat::Vec2));
	cellorigin.x = (position % cellperrow) * cell_size;
	cellorigin.y = (position / cellperrow) * cell_size;
	*(pointer + 0) = cellorigin;
	*(pointer + 1) = {cellorigin.x + cell_size, cellorigin.y};
	*(pointer + 2) = {cellorigin.x + cell_size, cellorigin.y + cell_size};
	*(pointer + 3) = {cellorigin.x, cellorigin.y + cell_size};
	esat::DrawSetFillColor(255,0,0);
	esat::DrawSolidPath(&(pointer + 0)->x, 4);
}

void DrawCells(){
	esat::Vec2 mouse = {(float)esat::MousePositionX(), (float)esat::MousePositionY()};
	for(int i = 0; i < total_cells; i++){
		if(esat::MouseButtonDown(0) && mouse.x > i * cell_size && mouse.x < (i + 1) * cell_size && mouse.y > (i) * cell_size && mouse.y < (i + 1) * cell_size)
			*(cells+i) = !(*(cells + i));
		if(*(cells + i) == 1){
			DrawSquare(i);
		}
	}
}



void Init(){
	InitCells();
}

void Update(){
	for(int i = 0; i < total_cells; i++){
		UpdateCell((cells + i), (nextgen + i), i);
	}
	for(int i = 0; i < total_cells; i++){
		*(cells + i) = *(nextgen + i);
	}
}
void Draw(){
	// DrawDungeon();
	DrawCells();
}


int esat::main(int argc, char **argv) {

	if(argc != 3){
		printf("Error. Faltan argumentos para la funcion Main");
	}else{
		//Recogida de los argumentos
		cellperrow = atoi(*(argv + 2));
		cell_size = 800 / cellperrow;
		total_cells = cellperrow * cellperrow;
		DivideNumbers(*(argv + 1));
	
		printf("Condiciones de Supervivencia: %d, %d\nCondicion de Nacimiento: %d",*(survivalcondition + 0), *(survivalcondition + 1), birthcondition);

		

		//Inicio del programa
		Init();
		esat::WindowInit(800, 800);
		WindowSetMouseVisibility(true);

		while (esat::WindowIsOpened() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape))
		{

			last_time = esat::Time();
			esat::DrawBegin();
			esat::DrawClear(0, 0, 0);
			if(esat::IsSpecialKeyPressed(esat::kSpecialKey_Keypad_1)){
				Update();
			}
			Draw();
			esat::DrawEnd();

			// Control fps
			do
			{
				current_time = esat::Time();
			} while ((current_time - last_time) <= 1000.0 / fps);
			esat::WindowFrame();
	}
  }
  esat::WindowDestroy();
  return 0;
}

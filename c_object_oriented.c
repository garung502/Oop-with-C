// EX1
	// C++ code
	object->method(some_args);
	// C code
	method(object, some_args);
/*----------------------------------------------------------- C++ --------------------------------------------------------------------*/
class Rectange {
	private:
		int x, y;
		int width;
		int height;
	public:
		// getters, setters , if need
		void draw();
};

void Rectange::draw() {
	std::cout << "Just drew a nice " << width << "by" << height <<
						"rectangle at position  (" << x << ", " << y << ") !";
}

/*----------------------------------------------------------- C ----------------------------------------------------------------------------*/
typedef struct Rectange {
	int x, y;
	int width;
	int height;
} Rectange;

void draw(Rectange* obj) {
	printf("Just drew a nice %d by %d rectangle at positon (%d, %d) ! ", obj->width, obj->height, obj->x, obj->y);
}

// Create object after call methord 
// For C++:
Rectange* r = new Rectange();
r->draw();
//For C:
Rectange* r = (Rectange*) malloc(sizeof(Rectange));
draw(r);

// Constructor 
//For C++:
Rectange::Rectange(int initx, int inity,
							  int initw, int inith) {
	x = initx;
	y = inity;
	width = initw;
	height = inith;
}
// use
Rectange* r = new Rectange(1, 2, 3, 4);

// For C:
Rectange* Rectange_init(int initx, int inity,
									int initw, int inith) {
	struct Rectange* r = (Rectange*) malloc(sizeof(Rectange));
	r->x = initx;
	r->y = inity;
	r->width = initw;
	r->height = inith;
	
	return r;
}

// EX2 : Inheritance
/*---------------------------------------------------------------------------------- C++ ---------------------------------------------------------------------------*/
class Shape {
	/* Shape class members */
};

class Rectange : public Shape {
	/* Rectange class members */
};

/*-------------------------------------------------------------------------------- C --------------------------------------------------------------------------------*/
struct Shape {
	/* base class members */
};

struct Rectange {
	struct Shape supper;
	/* derived class membees */
};

//EX3: Polymoprihism
/*-------------------------------------------------------------------------------- C++ ------------------------------------------------------------------------------*/
// Shape abstract interface
class Shape {
	public:
		virtual void draw() = 0;
		virtual void moveTo(int newx, int newy) = 0;
};

// Rectange class
class Rectange : public Shape {
	private:
		int x, y;
		int width, height;
	public:
		Rectange(int initx, int inity, int initw, int inith);
		
		int getX() { return this->x; }
		int getY() { return this->y; }
		int getWidth() { return this->width; }
		int getHeight() { return this->height; }
		
		void setX(int newx) { this->x = newx; }
		void setY(int newy) { this->y = newy;}
		void setWidth(int neww) { this->width = neww; }
		void setHeight(int newh) { this->height = newh; }
		
		virtual void draw();
		virtual void moveTo(int newx, int newy);
};

Rectange::Rectange(int initx, int inity, int initw, int inith) {
	x = initx;
	y = inity;
	width = initw;
	height = inith;
}

void Rectange::draw() {
	std::cout << "Just drew a nice " << width << "by" << height <<
						"rectangle at position  (" << x << ", " << y << ") !";
}

void Rectange::moveTo(int newx, int newy) {
	x = newx;
	y = newy;
	
	std :: cout << " Moving your rectangle to ( " << x
					<< " , " << y << " ) ! " << std :: endl ;
}

// Circle class
class Circle : public Shape {
	private:
		int x, y;
		int radius;
	public:
		Circle(int intx, int inity, int initr);
		virtual void draw();
		virtual void moveTo(int newx, int newy);
		
		int getX() { return this->x; }
		int getY() { return this->y; }
		int getRadius() { return this->radius; }
		
		void setX(int newx) { this->x = newx; }
		void setY(int newy) { this->y = newy; }
		void setRadius(int newr) {this->radius = newr; }
};

Circle::Circle(int intx, int inity, int initr) {
	x = initx;
	y = inity;
	radius = initr;
}

void Circle :: draw () {
std :: cout << " Just drew a perfect circle of radius "
<< radius << " at position ( "
<< x << " , " << y << " ) ! " << std :: endl ;
}
void Circle :: moveTo ( int newx , int newy ) {
x = newx ;
y = newy ;
std :: cout << " Moving your circle to ( " << x
<< " , " << y << " ) ! " << std :: endl ;
}

/* A function that uses a Shape polymorphically */
void handleShape(Shape* s) {
	std::cout << " Bad shape ! Go to the corner ! " << std :: endl ;
	s->moveTo(0, 0)
}

int main() {
	Shape* shapes[2];
	shapes[0] = new Rectange(20, 12, 123, 321);
	shapes[1] = new Circle(21, 12, 2012);
	
	for(int i = 0; i < 2; i++) {
		shapes[i]->draw();
		handleShape(shapes[i]);
	}
	
	//Acces a specific class function 
	Rectange* r = new Rectange(1, 2, 3, 4);
	r->setWidth(5);
	r->draw();
	return 0;
}

/*-------------------------------------------------------------------------------------- C -------------------------------------------------------------------------------*/
// Shape abstract interface
struct Shape {
	struct ShapeFuncTabe* funcTable;
};

struct ShapeFuncTabe {
	void (*draw) (struct Shape* obj);
	void (*moveTo) (struct Shape* obj, int newx, int newy);
	void (*destructor_) (struct Shape* obj);
};

struct Shape* Shape_init() { assert(0); }
void Shape_destroy(struct Shape* obj) {}

// Rectange class
struct Rectange {
	struct Shape supper;
	int x, y;
	int width, height;
};

void Rectange_draw(struct Shape* obj) {
	struct Rectange* rdata = (struct Rectange*) obj;
	
	printf ( " I just drew a nice % d by % d rectangle at position (% d , % d ) ! \ n " , 
				rdata - > width , rdata - > height , rdata - >x , rdata - > y ) ;
}

void Rectange_moveTo(struct Shape* obj, int newx, int newy) {
	struct Rectange* rdata = (struct Rectange*) obj;
	rdata->x = newx;
	rdata->y = newy;
	
	printf ( " Moving your rectangle to (% d , % d ) \ n " , rdata - >x , rdata - > y ) ;
}

void Rectange_setWidth(struct Shape* obj, int neww) {
	struct Rectange* rdata = (struct Rectange*) obj;
	
	rdata->width = neww;
}

void Rectange_destroy(struct Shape* obj) {
	Shape_destroy(obj);
	free(obj);
}

struct RectangeFuncTable {
	struct ShapeFuncTabe supper;
	void (*setWidth) (struct Shape* obj, int newx);
}

RectangeFuncTable rectangleFuncTable = {
	{  Rectange_draw,
	   Rectange_moveTo,
	   Rectange_destroy
	},
	Rectange_setWidth
};

struct Shape* Rectange_init(int initx, int inity, int initw, int inith) {
	struct Rectange* obj  = (struct Rectange*) malloc(sizeof(Rectange));
	
	obj->supper.funcTable = (struct RectangeFuncTable*) &rectangleFuncTable;
	obj->x = initx;
	obj->y = inity;
	obj->width = initw;
	obj->height = inith;
	
	return (struct Shape*)obj;
}

//Circle class
struct Circle {
	struct Shape supper;
	int x, y;
	int radius;
};

void Circle_draw(struct Shape* obj) {
	struct Circle* cdata = (struct Circle*)obj;
	printf ( " Just drew a perfect circle of radius % d at position (% d , % d ) !\ n " , 
				cdata - > radius , cdata - >x , cdata - > y ) ;
}

void Circle_moveTo(struct Shape* obj, int newx, int newy) {
	struct Circle* cdata = (struct Circle*) obj;
	
	obj->x = newx;
	obj->y = newy;
	
	printf ( " Moving your circle to (% d , % d ) \ n " , cdata - >x , cdata - > y ) ;
}

void Circle_destroy(struct Shape* obj) {
	Shape_destroy(obj);
	free(obj);
}

struct CircleFuncTable {
	struct ShapeFuncTabe supper;
};

struct CircleFuncTable circleFuncTable {
	Circle_draw,
	Circle_moveTo,
	Circle_destroy
};

struct Shape* Circle_init(int initx, int inity, int initr) {
	struct Circle* obj = (Circle*)malloc(sizeof(Circle));
	
	obj->supper.funcTable = (struct ShapeFuncTabe*) &circleFuncTable;
	
	obj->x = initx;
	obj->y = inity;
	obj->radius = initr;
	
	return (Shape*) obj;
}

# define Shape_DRAW ( obj )							( (struct Shape*)(obj)->funcTable->draw( (obj) ) )
# define Shape_MOVETO(obj, newx, newy)		( (struct Shape*)(obj)->funcTable->moveTo( (obj), (newx), (nexy) ) )
# define Rectange_SETWIDTH(obj, width)		( (struct Shape*)(obj)->funcTable->setWidth( (obj), (width) ) )
# define Shape_DESTROY(obj) 						( (struct Shape*)(obj)->funcTable->destructor_( (obj) ) )

/* A function that uses a shape polymorphically */
void handleShape( struct Shape* s ) {
	Shape_MOVETO(s, 0, 0);
}

int main() {
	int i;
	struct Shape* shapes[2];
	struct Shape* r;
	/* using Shape polymorphically */
	shapes[0] = Rectange_init(1, 2, 3, 4);
	shapes[1] = Circle_init(10, 20, 30);
	
	for(i = 0; i < 2; i++) {
		Shape_DRAW( shapes[i] );
		handleShape( shapes[i]) ;
	}
	
	/* accessing Rectange specific data */
	r = Rectange_init(2, 4, 6, 8);
	Rectange_SETWIDTH(r, 5);
	
	Shape_DRAW( r );
	Shape_DESTROY( r );
	
	for( i = 1; i >= 0; --i ) {
		Shape_DESTROY( shapes[i] );
	} 
}
/*
 * Vector2.h
 *
 * cite Sergi ThreeVector
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_

class Vector2 {
public:
    //Default constructor.
    Vector2();
    //component constructor.
    Vector2(double x, double y);

    //array constructor
    Vector2(const double *);

    //copy constructor. passed by reference.
    Vector2(const Vector2 &);

    //destructor.
    virtual ~Vector2();

	//Declaration of access methods. inline instructs the compiler to replicate
	//the corresponding machine code each time they are invoked, rather than
	//jumping to the position of a single copy of machine code; this results in
	//faster execution, but larger executables. Declaring a method inline requires
	//the implementation to be done in the same file. const indicates that the object is not
	//modified by the execution of the method, thus the compiler can perform some
	//optimization
	//The components in cartesian coordinate system.
	inline double x()  const;
	inline double y()  const;

	inline double X()  const;
	inline double Y()  const;

	inline double Px() const;
	inline double Py() const;


	//inline but not const, since they are meant to modify the object
	//Set the components
	inline void SetX(double);
	inline void SetY(double);
    inline void SetXY(double x, double y);

	//inline and const can be used wherever convenient and possible (const cannot be used
	//if something is modified during the execution) to optimize the code
	//Scalar product.
    inline double Dot(const Vector2 &) const;

	//The transverse component (R in cylindrical coordinate system).
    //double Perp() const;

	//The transverse component squared (R^2 in cylindrical coordinate system)
    //inline double Perp2() const;

	//The transverse component w.r.t. given axis squared.
    //inline double Perp2(const Vector2 &) const;

	//The transverse component w.r.t. given axis.
    //double Perp(const Vector2 &) const;

	//The azimuth angle. returns phi from -pi to pi
    //double Phi() const;

	//The polar angle.
    //double Theta() const;

    //The magnitude squared (length of the vector^2).
	inline double Mag2() const;

    //The magnitude (length of the vector).
	double Mag() const;

	//Declaration of operators acting on the invoking instance; they could be implemented
	//here or in the implementation file, if they were not declared inline
	//Assignment.
    inline Vector2 & operator = (const Vector2 &);

	//Addition.
    inline Vector2 & operator += (const Vector2 &);

	//Subtraction.
    inline Vector2 & operator -= (const Vector2 &);

	//Unary minus.
    inline Vector2 operator - () const;

	//Scaling with real numbers.
    inline Vector2 & operator *= (double);

	//Unit vector parallel to this.
    Vector2 Unit() const;

	//Printing the content in a convenient way
	void Print() const;

private:

    double fX, fY;
	// The components.
};

//Declaration of operators without an invoking instance. They must be global, thus
//declared outside the scope of the class
//Addition of 2-vectors.
Vector2 operator + (const Vector2 &, const Vector2 &);

//Subtraction of 2-vectors.
Vector2 operator - (const Vector2 &, const Vector2 &);

//Scaling of 2-vectors with a real number
Vector2 operator * (const Vector2 &, double a);
Vector2 operator * (double a, const Vector2 &);

//comparison operator
bool operator == (const Vector2 &, const Vector2 &);

//Implementation of all methods and operators declared inline
inline double Vector2::x()  const { return fX; }
inline double Vector2::y()  const { return fY; }

inline double Vector2::X()  const { return fX; }
inline double Vector2::Y()  const { return fY; }

inline double Vector2::Px() const { return fX; }
inline double Vector2::Py() const { return fY; }

//want Vx, Vy?

inline void Vector2::SetX(double xx) { fX = xx; }
inline void Vector2::SetY(double yy) { fY = yy; }


inline void Vector2::SetXY(double xx, double yy) {
   fX = xx;
   fY = yy;
}

//inline double Vector2::Perp2() const { return fX*fX + fY*fY; }

inline double Vector2::Mag2() const { return fX*fX + fY*fY; }

inline double Vector2::Dot(const Vector2 & p) const {
   return fX*p.fX + fY*p.fY;
}

//inline double Vector2::Perp2(const Vector2 & p)  const {
//   double tot = p.Mag2();
//   double ss  = Dot(p);
//   double per = Mag2();
//   if (tot > 0.0) per -= ss*ss/tot;
//   if (per < 0)   per = 0;
//   return per;
//}

//All operators involving assignment return the invoking instance itself
//by dereferencing the pointer this
inline Vector2 & Vector2::operator = (const Vector2 & p) {
   fX = p.fX;
   fY = p.fY;
   return *this;
}

inline Vector2& Vector2::operator += (const Vector2 & p) {
   fX += p.fX;
   fY += p.fY;
   return *this;
}

inline Vector2& Vector2::operator -= (const Vector2 & p) {
   fX -= p.fX;
   fY -= p.fY;
   return *this;
}

inline Vector2 Vector2::operator - () const {
   return Vector2(-fX, -fY);
}

inline Vector2& Vector2::operator *= (double a) {
   fX *= a;
   fY *= a;
   return *this;
}

#endif /* VECTOR2_H_ */

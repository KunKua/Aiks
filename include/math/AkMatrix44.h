/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * ********************************************/

#ifndef AK_MATH_MATRIX44_H
#define AK_MATH_MATRIX44_H

namespace aiks {

/***************************
 *  0  1  2  3
 *  4  5  6  7
 *  8  9 10 11
 * 12 13 14 15
 * *************************/

template<typename F>
class TMatrix44
{
public:
    
    TMatrix44(F m00, F m01, F m02, F m03,
             F m10, F m11, F m12, F m13,
             F m20, F m21, F m22, F m23,
             F m30, F m31, F m32, F m33);
    TMatrix44(F mat[16]);
    ~TMatrix44();

    inline TMatrix44& operator =(const TMatrix44<F>& m)
    TMatrix44& operator*=(const TMatrix44& m);
    TMatrix44& operator+=(const TMatrix44& m);
    
	static TMatrix44<F>* identity();
    void toIdentity();
	void transpose();
	TMatrix44<F> getTranspose() const;
	inline F determinant() const
	{
		//ambiguous: only the upper-left-submatrix's determinant is calculated		
		return (_mat[0] * _mat[5] * _mat[10]) + (_mat[1] * _mat[6] * _mat[8]) + (_mat[2] * _mat[4] * _mat[9])
			   	- (_mat[0] * _mat[6] * _mat[9]) - (_mat[1] * _mat[4] * _mat[10]) - (_mat[2] * _mat[5] * _mat[8]);
	}

	//transform a vector
	Vec3 transformVector(const Vec3& b) const;
	//trnasform a point
	Vec3 transformPoint(const Vec3& b) const;
    
	inline F* getData() 			{ return _mat; };
	inline const F* getData() const { return _mat; };

	inline F               operator()(u32 i, u32 j) const    { AK_MATH_ASSERT((i < 4) && (j < 4)); return _mat[i * 4 + j]; }
	inline F&              operator()(u32 i, u32 j)          { AK_MATH_ASSERT((i < 4) && (j < 4)); return _mat[i * 4 + j]; }

	inline void               setRow(int i, const TVec3<F>& v)     { AK_MATH_ASSERT(i < 4); _mat[0 + 4 * i] = v._x; _mat[1 + 4 * i] = v._y; _mat[2 + 4 * i] = v._z; }
	inline void               setRow4(int i, const TVec4<F>& v)    { AK_MATH_ASSERT(i < 4); _mat[0 + 4 * i] = v._x; _mat[1 + 4 * i] = v._y; _mat[2 + 4 * i] = v._z; _mat[3 + 4 * i] = v._w; }
	inline const TVec3<F>& getRow(int i) const                     { AK_MATH_ASSERT(i < 4); return *(const TVec3<F>*)(_mat + 4 * i); }
	inline const TVec4<F>& getRow4(int i) const                    { AK_MATH_ASSERT(i < 4); return *(const TVec4<F>*)(_mat + 4 * i); }

	inline void               setColumn(int i, const TVec3<F>& v)  { AK_MATH_ASSERT(i < 4); _mat[i + 4 * 0] = v._x; _mat[i + 4 * 1] = v._y; _mat[i + 4 * 2] = v._z; }
	inline void               setColumn4(int i, const TVec4<F>& v) { AK_MATH_ASSERT(i < 4); _mat[i + 4 * 0] = v._x; _mat[i + 4 * 1] = v._y; _mat[i + 4 * 2] = v._z; _mat[i + 4 * 3] = v._w; }
	inline TVec3<F>        getColumn(int i) const                  { AK_MATH_ASSERT(i < 4); return TVec3<F>(_mat[i + 4 * 0], _mat[i + 4 * 1], _mat[i + 4 * 2]); }
	inline TVec4<F>        getColumn4(int i) const                 { AK_MATH_ASSERT(i < 4); return TVec4<F>(_mat[i + 4 * 0], _mat[i + 4 * 1], _mat[i + 4 * 2], _mat[i + 4 * 3]); }

	inline Vec3               getTranslate() const                  { return Vec3(_mat[3], _mat[7], _mat[11]); }
	inline void               setTranslate(const Vec3& t)           { _mat[3] = t._x; _mat[7] = t._y; _mat[11] = t._z; }

private:
    F _mat[16]; 
};

typedef TMatrix44<f32>  Matrix44;   //!< Always 32 bit.
typedef TMatrix44<f64>  Matrix44d;  //!< Always 64 bit.

}

#endif /* AkMatrix44_h */

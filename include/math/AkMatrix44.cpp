/************************************************
 * Copyright 2016 Aiks Group,All rights reserved.
 * *********************************************/

#include "math/AkMatrix44.h"

namespace aiks {
    template<typename F>
    TMatrix44::TMatrix44(F _mat[0], F _mat[1], F _mat[2], F _mat[3],
                       F _mat[4], F _mat[5], F _mat[6], F _mat[7],
                       F _mat[8], F _mat[9], F _mat[10], F _mat[11],
                       F _mat[12], F _mat[13], F _mat[14], F _mat[15]){
			_mat[0] = _mat[0]; _mat[1] = _mat[1]; _mat[2] = _mat[2]; _mat[3] = _mat[3];
			_mat[4] = _mat[4]; _mat[5] = _mat[5]; _mat[6] = _mat[6]; _mat[7] = _mat[7];
			_mat[8] = _mat[8]; _mat[9] = _mat[9]; _mat[10] = _mat[10]; _mat[11] = _mat[11];
			_mat[12] = _mat[12]; _mat[13] = _mat[13]; _mat[14] = _mat[14]; _mat[15] = _mat[15];  
    }
    
    template<typename F>
	TMatrix44::TMatrix44(F mat[16]){
        memcpy(_mat, mat, sizeof(F) * 16);
    }

    template<typename F>
    TMatrix44& TMatrix44::identity(){
		TMatrix44<F>* ma = new TMatrix44<F>();
		ma->toIndentity();	
        return *ma;
    }
    
    template<typename F>	
    void TMatrix44::toIdentity(){
        _mat[1] = _mat[2] = _mat[3] = _mat[4]
			  = _mat[6] = _mat[7] = _mat[8] = _mat[9]
		      = _mat[11] = _mat[12] = _mat[13] = _mat[14] = F(0);
        _mat[0] = _mat[5] = _mat[10] = _mat[15] = F(1);
    }

    template<typename F>
	TMatrix44& TMatrix44::operator =(const TMatrix44<F>& m)
	{
		F* p = m.getData();
		_mat[0] = p[0];
		_mat[1] = p[1];
		_mat[2] = p[2];
		_mat[3] = p[3];
		_mat[4] = p[4];
		_mat[5] = p[5];
		_mat[6] = p[6];
		_mat[7] = p[7];
		_mat[8] = p[8];
		_mat[9] = p[9];
		_mat[10] = p[10];
		_mat[11] = p[11];
		_mat[12] = p[12];
		_mat[13] = p[13];
		_mat[14] = p[14];
		_mat[15] = p[15];

		return *this;
	}	
    
    TMatrix44 TMatrix44::operator*=(TMatrix44 &m){
        auto tmp = new float[16];
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                int dest = i * 4 + j;
                tmp[dest] = this->mat[i * 4] * m.mat[j] +
                            this->mat[i * 4 + 1] * m.mat[j + 4] +
                            this->mat[i * 4 + 2] * m.mat[j + 8] +
                            this->mat[i * 4 + 3] * m.mat[j + 12];
            }
        }
        
        memcpy(this->mat, tmp, sizeof(float) * 16);
        delete[] tmp;
        
        return *this;
    }
    
    TMatrix44 TMatrix44::operator+=(TMatrix44 &m){
        for(int i = 0; i < 16; i++){
            this->mat[i] = this->mat[i] + m.mat[i];
        }
        
        return *this;
    }

    template<typename F>
	void transpose()
	{
		TMatrix44<F> tmp = *this;
		_max[0] = tmp._max[0];
		_mat[1] = tmp._mat[4];
		_mat[2] = tmp._mat[8];
		_mat[3] = tmp._mat[12];
		_mat[4] = tmp._mat[1];
		_mat[5] = tmp._mat[5];
		_mat[6] = tmp._mat[9];
		_mat[7] = tmp._mat[13];
		_mat[8] = tmp._mat[2];
		_mat[9] = tmp._mat[6];
		_mat[10] = tmp._mat[10];
		_mat[11] = tmp._mat[14];
		_mat[12] = tmp._mat[3];
		_mat[13] = tmp._mat[7];
		_mat[14] = tmp._mat[11];
		_mat[15] = tmp._mat[15];
	}

    template<typename F>	
	TMatrix44<F>& getTranspose() const
	{
		TMatrix44<F> tmp;
		tmp._mat[0] = _mat[0];
		tmp._mat[1] = _mat[4];
		tmp._mat[2] = _mat[8];
		tmp._mat[3] = _mat[12];
		tmp._mat[4] = _mat[1];
		tmp._mat[5] = _mat[5];
		tmp._mat[6] = _mat[9];
		tmp._mat[7] = _mat[13];
		tmp._mat[8] = _mat[2];
		tmp._mat[9] = _mat[6];
		tmp._mat[10] = _mat[10];
		tmp._mat[11] = _mat[14];
		tmp._mat[12] = _mat[3];
		tmp._mat[13] = _mat[7];
		tmp._mat[14] = _mat[11];
		tmp._mat[15] = _mat[15];
		return tmp;
	}

    template<typename F>	
	Vec3 transformVector(const Vec3& b) const
	{
		Vec3 v;
		v.x = _mat[0] * b.x + _mat[1] * b.y + _mat[2] * b.z;
		v.y = _mat[4] * b.x + _mat[5] * b.y + _mat[6] * b.z;
		v.z = _mat[8] * b.x + _mat[9] * b.y + _mat[10] * b.z;
		return v;
	}

    template<typename F>	
	Vec3 transformPoint(const Vec3& b) const
	{
		Vec3 v;
		v._x = _mat[0] * b._x + _mat[1] * b._y + _mat[2] * b._z + _mat[3];
		v._y = _mat[4] * b._x + _mat[5] * b._y + _mat[6] * b._z + _mat[7];
		v._z = _mat[8] * b._x + _mat[9] * b._y + _mat[10] * b._z + _mat[11];
		return v;
	}

    TMatrix44::~TMatrix44(){
    }

}

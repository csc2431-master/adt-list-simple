/*
 * Title:		Integer wrapper Class
 * Purpose:		A subclass of object to wrap up an integer
 * Author:		Carlos Arias
 * Date:		April 29, 2020
 */
#ifndef INTEGER_H
#define INTEGER_H

#include "object.h"

#include <string>
using std::string;

class Integer : public Object{
		int _value;
	public:
		Integer(int = 0);
		virtual string ToString()const;
		int GetValue()const;
		void SetValue(int);
		virtual bool Equals(const Object& rhs)const;
		virtual Object* Clone()const;
};

#endif /* end of include guard: INTEGER_H */

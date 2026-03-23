#pragma once
#ifndef BOOK_H_
#define BOOK_H_
#include<iostream>
#include<string>
using namespace std;
class Student {
	string stu_name;
	int stu_id;
public:Student(const string &s1,int n1):stu_name(s1),stu_id(n1){}
	  explicit Student(int n1):Student("none",n1){}
	  explicit Student(const string& s1) :Student(s1, 0) {}
	  Student() :Student("none", 0) {}
	  virtual void change();
	  void Show()const;
	  friend ostream& operator<<(ostream& os, const Student& s1);
	  friend istream& operator>>(istream& is, Student& s1);
	  bool operator==(const Student& s1) const{ return (stu_name == s1.stu_name && stu_id == s1.stu_id); }
};

class Bookbase {
	string bookname;
	string writer;
public:Bookbase(const string& s1, const string& s2) :bookname(s1), writer(s2) {}
	  explicit Bookbase(const string& s1) :bookname(s1), writer("none") {}
	  virtual const string& findtool() { return bookname; }

	  void change();
	  void Show()const;
	  virtual ~Bookbase() ;
	  friend ostream& operator<<(ostream& os, const Bookbase& s1);
	  friend istream& operator>>(istream& is,  Bookbase& s1);
	  bool operator==(const Bookbase& b1)const { return (bookname == b1.bookname && writer == b1.writer); }
};

class Borrow :public Student,public Bookbase{
private:
	string bor_time;
public:Borrow(const string&s4="none", int n=0, const string& s1="none", const string& s2="none",
	const string& s3="none") :Bookbase(s1, s2),
	Student(s4,n),bor_time(s3){}
	  Borrow(int n, const string& s1, const string& s2, const string& s3) :Student(n), Bookbase(s1, s2),
		  bor_time(s3) {
	  }
	  Borrow(const Student&s1, const string& s4, const string& s2, const string& s3):Student(s1),
		  Bookbase(s4, s2), bor_time(s3){ }
	  Borrow(const Student& s1, const Bookbase& b1, const string& s2) :Student(s1), Bookbase(b1), 
		  bor_time(s2) {}
	  Borrow(const Borrow& b1) :Student(b1), Bookbase(b1) {
		  bor_time = b1.bor_time;
	  }
	  
	  bool operator==(const Borrow& b1)const;
	  void change();
	  void Show()const;
	  friend ostream& operator<<(ostream& os, const Borrow& s1);
	  friend istream& operator>>(istream& is,  Borrow& s1);
};
class Book:public Bookbase
{
private:
	double price;
	int number_all;
	int number_now;
public:Book(const string& s1="none", const string& s2="none", double b1=0, int n1=0, int n2=0) :Bookbase(s1, s2),
	price(b1), number_all(n1), number_now() {
}
	  Book(const string& s1, double b1, int n1, int n2) :Book(s1, "none", b1, n1, n2) {}
	  bool bor_book() {
		  if (number_now == 0)
		  {
			  cout << "Sorry,no have.\n";
			  return false;
		  }
		  else --number_now;
		  return true;
	  }
	  bool repay() {
		  ++number_now;
		  return true;
	  }

	  void change();
	  void Show()const;
	  friend ostream& operator<<(ostream& os, const Book& s1);
	  friend istream& operator>>(istream& is,  Book& s1);
	  bool operator==(const Book& b1)const;
	  
};

class User {
	string uname;
	int upossard;
public:User() :uname("none"), upossard(0) {}
	  User(const string& s1, int n) :uname(s1 ), upossard(n) {}
	  void change();
	  friend ostream& operator<<(ostream& os, const User& u1) {
		  os << u1.uname << endl;
		  os << u1.upossard << endl;
		  return os;
	  }
	  friend istream& operator>>(istream& is,  User& u1);
	  bool operator==(const User& u1)const;
};

class Admin {
	string adm_name;
	int adm_possard;
public:Admin(): adm_name("none"), adm_possard(0) {}
	  Admin(const string& s1, int n) :adm_name(s1), adm_possard(n) {}
	  void change();
	  friend ostream& operator<<(ostream& os, const Admin& u1);
	  friend istream& operator>>(istream& is,  Admin& u1);
	  bool operator==(const Admin& a1)const { return(adm_name == a1.adm_name && adm_possard == a1.adm_possard); }
};

#endif
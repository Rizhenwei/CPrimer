#pragma once
#pragma execution_character_set("utf-8")
#include<iostream>
#include<string>
using namespace std;
class Item_base
{
public:
	Item_base(const string &book = "", double sales_price = 0.0) :
		isbn(book), price(sales_price){}
	string book()const{ return isbn; }
	virtual double net_price(size_t n)const
	{
		return n*price;
	}
	virtual~Item_base(){}

private:
	string isbn;
protected:
	double price;
};
class LD_item:public Item_base
{
public:
	LD_item(const string&book="",double sales_price=0.0,size_t qty=0,double dis_rate=0.0):
		Item_base(book, sales_price), max_qty(qty), discount(dis_rate){}
	virtual~LD_item(){}
	double LD_item::net_price(size_t cnt)const
	{
		if (cnt <= max_qty)
			return cnt*(1 - discount)*price;
		else
		{
			return cnt*price - max_qty*discount*price;
		}
	}
private:
	size_t max_qty;
	double discount;
};
void print_total(ostream&os, const Item_base &item, size_t n)
{
	os << "ISBN:" << item.book()
		<< "\tnumber sold:" << n << "\ttotal price:"
		<< item.net_price(n) << endl;
}
int main()
{
	LD_item ld1("021-15879-5874-79", 5.5, 100, 0.8);;
	LD_item ld2("021-15879-5874-78", 5.5, 100, 0.8);
	double res1 = ld2.net_price(80);
	double res2=ld2.net_price(120);
	cout << "ld1 net_price:" << res1
		<< "\tld2 net_price:" << res2 << endl;	
	print_total(cout, ld1, 10);
	return 0;
}

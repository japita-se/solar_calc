#ifndef SECANT_H
#define SECANT_H

#include "assert.h"
#include "math.h"
#include <QDebug>
#include <QPolygonF>
#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct {
    double (*user_func) (double,double,double,double);
    double Fin;
    double A;
    double rate;
 } callback;

double bisection(callback* c,double a0,double b0, double eps, int maxit)
{
double ak,bk,ck,yk,y0,y1,yh;
double n=0;
            y0 = c->user_func( (a0),c->A,c->Fin,c->rate);
            y1 = c->user_func( (b0),c->A,c->Fin,c->rate);
            ak = a0;
            bk = b0;

            if (y0*y1>0)
                    return 0; // no change in sign
            do {
                ck = 0.5 * (ak + bk);
                yk = c->user_func( (ck),c->A,c->Fin,c->rate);
                yh = c->user_func( (bk),c->A,c->Fin,c->rate);


                if (fabs(yk)<eps)
                    return ck;
                if ((yh*yk)>0)
                        bk = ck;
                if ((yh*yk)<0)
                        ak = ck;

                n++;
            } while (n < maxit   );

                return ck;

}
typedef struct {
    double (*user_func) (double,QPolygonF,double,double);
    double Fin;
    QPolygonF A;
    double rate;
 } callback2;
double bisection(callback2* c,double a0,double b0, double eps, int maxit)
{
double ak,bk,ck,yk,y0,y1,yh;
double n=0;
            y0 = c->user_func( (a0),c->A,c->Fin,c->rate);
            y1 = c->user_func( (b0),c->A,c->Fin,c->rate);
            ak = a0;
            bk = b0;
//qDebug()<<"SECANT "<<y0<<y1<<c->A.size()<<c->Fin<<c->rate<<n;
            if (y0*y1>0)
                    return -1; // no change in sign

            do {
             //   qDebug()<<"SECANT "<<y0<<y1<<c->A.size()<<c->Fin<<c->rate<<n;
                ck = 0.5 * (ak + bk);
                yk = c->user_func( (ck),c->A,c->Fin,c->rate);
                yh = c->user_func( (bk),c->A,c->Fin,c->rate);


                if (fabs(yk)<eps)
                    return ck;
                if ((yh*yk)>0)
                        bk = ck;
                if ((yh*yk)<0)
                        ak = ck;

                n++;
            } while (n < maxit   );

                return ck;

}
double secant(callback* c , double x0, double x1,double eps,int maxit)
{


    assert(x0 < x1);

        double x;

        int n = 0;
        do {

            double y0 =   c->user_func(x0,c->A,c->Fin,c->rate),
                   y1 =  c->user_func(x1,c->A,c->Fin,c->rate);
qDebug()<<"SECANT "<<x0<<x1<<c->A<<c->Fin<<c->rate<<y0<<y1<<n;


            x = y0 * ((x0  - x1 ) / (y0- y1)), x1 = x0, x0 = x0 -x;
            if (fabs(x) < eps)
                return x0;
            n++;


        } while (n < maxit );

        return x0;
    }
#endif // SECANT_H

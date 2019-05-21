#ifndef __mymath_h
#define __mymath_h
#include <vector>
#include <QPointF>
#include <QStringList>
#include <QFile>
#include <QDate>
#include "data.h"
typedef  double (*user_func)(int n);
class QPolygonF;
class MyMath {

public:
	MyMath();
	~MyMath();
        static bool isEtero(const QStringList &a);
        static int findPoint(loc localita, const QVector<int> &index,const QPolygonF & region,int rSize);
        static  int countCross(const QPolygonF &a);
        static int npvCross(const QPolygonF &a);
        static QVector<double> seekInFile(const QString file,qint64 pos,int length);
        static QString toString(const QPolygonF &a,QString &s);
        static QString toString(const QVector<double> &a,QString &s);
        static QPolygonF subtract(const QPolygonF &a,const QPolygonF &b);
        static QPolygonF add(const QPolygonF &a,const QPolygonF &b);
        static double inflate(int year,double rate,double value);
        static double min(const QPolygonF& a);
        static QVector<double> loadFromText( QString& fileName);
        static QPolygonF cumulative(const QPolygonF& a);

        static double convertToDouble(const QString &input);
	static QVector<int>  numOfWeekendsAndRests(QDate a,int day);
	static void scale(QVector<double> &a,double v);
	static void scale(QPolygonF &a,double v);
        static bool exportToText(QString& fileName,QVector<double>& a);
	static bool exportToText(QString& fileName,double* data,int size);
	static bool exportToText(QString& f,QPolygonF& data);
	static double W_1(double hour,double T);
        static QVector<int> toVector(const QStringList &a);
        static QVector<double> toVectorDouble(const QStringList &a);
	static QStringList toStringList(const QVector<int> &a);
        static QStringList toStringList(const QVector<double> &a);
        static QStringList toStringList(double *a,int size);
	static QVector<int> serie(int start, int stop);
	static QString  serieCellTable(int start, int stop);
	static int refDay(int month);
	static int refMonthDay(int m);
	static QVector<double> tiltedRiseSet(double tilt,double azimuth,double latitude,int month);
	static void tiltedRiseSet(double tilt,double decl,double azimuth,double latitude,double os ,double *out);
	static QVector<double> rb(double lat, double localIncl,double azi,int m,int year,int mode);
	static double mean(const QVector<double>& a);
	static double mean(const QPolygonF& a);
	static double realNoct(double t,int mounting,double mountingHeight);
	static QStringList listOfNumber(int start, int stop);
	static QStringList monthFull();
	static QStringList nullList();
	static double pwf(double D, int n);
	static double uniform();
	static double var(const QVector<double> &a);
	static double randn();
        static QString monthsIta(int i);
	static QStringList monthsList();
	static int yearEnd(int i);
	static bool leapYear(int year);
	static QStringList stringSerie(int start,int stop);
	static int dayOfYear(int year,int month, int day);
	static int pos(double a);
	static bool clockWise(double a, double b);
        static double convertCoFromDegree(double lat,double min,double sec);
	static double convertCoFromDegree(int lat,int min,int sec);
	static int sign(double a);
	static int degree(double a);
        static double minute(double a);
        static double seconds(double a);
	static double decimal(double m);
	static double linear(double x1,double y1,double x2,double y2, double x);
	static QString months(int i);
        static double min(const QVector<double> &y);
	static double min(double a, double b);
	static double min(double *a,int size);
        static double max(double *a,int size);
	static double max(const QVector<double> &y);
	static double max(const QPolygonF &y);
        static double max(double a, double b);
	static double cumSum(QVector<double> a, int s,int stop);
	static double cumSum(double *a,int size);
	static double cumSumMonthly(double *a,int size);
 	static double cumSum(QVector<double> a);
	static int cumSum(QVector<int> a);
        static double cumSum(const QPolygonF &a);
	static void convertToDegree(double* vec,int size);
        static QVector<double> convertToDegree(QVector<double> vec);
	static double leftValue(const QPolygonF &polygon);
	static double rightValue(const QPolygonF &polygon);
	static bool   isOrdered(const QPolygonF &polygon);
	static bool lessThanPoint(const QPointF &p1, const QPointF &p2);
	static int monthEnd(int mm,int year);
	static QString checkFormat(const QString &source,const QString &format);
// 	static double integrate(double a,double b);
enum {
		rack,
		direct,
		standoff	
	};
};
#endif

/*-------------------------------------------------------------------------*/
/*                        ECOLE DES MINES DE PARIS                         */
/*        CENTRE D'ENERGETIQUE - GROUPE TELEDETECTION & MODELISATION       */
/*                       Rue Claude Daunesse, BP 207                       */
/*                   06904 Sophia Antipolis cedex, FRANCE                  */
/*          Tel (+33) 04 93 95 74 49     Fax (+33) 04 93 95 75 35          */
/*                       E-mail : (name)@cenerg.cma.fr                     */
/*-------------------------------------------------------------------------*/
/*   L. Wald - O. Bauer - February 1997
/*                                     */
/*   modified 8 July 2004 L. Wald for geocentric - geographic lat          */
/*   modified by G. De Marco                                                 */
/*-------------------------------------------------------------------------*/

#include <math.h>
#include "myspa.h"
#include <stdio.h>
#define Pi  3.141592654
#define I0  1367.0  /* solar constant in W/m2 */
#define Dl  24.0 /* average value for the length of the day in decimal hours */

/*************/
/* NOTATIONS */
/*************/
/* phi_g  : geographic latitude of the site, positive to North */
/* phi    : geocentric latitude of the site, positive to North */
/* lambda : longitude of the site, positive to East */
/* delta  : solar declination angle */
/* omega  : solar hour angle */
/* gamma  : solar altitude (or elevation) angle */
/* theta  : solar incidence (or zenithal) angle (ESRA --> zeta) */
/* alpha  : solar azimuthal angle (or psi) */

/* t   : solar time = true solar time (TST) = local apparent time (LAT) */
/* LAT : local apparent time or solar time or true solar time (TST)
   --> this system of time offers the advantage of symmetry of the solar 
   geometry about the north-south line */
/* LMT : local mean time or clock time */
/* UT  : Universal Time, is GMT measured from Greenwich mean midnight */

/* omega_sr : sunrise hour angle */
/* omega_ss : sunset hour angle */
/* t_sr     : time of astronomical sunrise */
/* t_ss     : time of astronomical sunset */

/* omega1 : solar hour angle at beginning of the time period */
/* omega2 : solar hour angle at end of the time period */

/* S0  : astronomical daylength or astronomical sunshine duration */
/* I0  : solar constant = annual mean value of extraterrestrial direct solar 
   irradiance G0 (1367.0 W/m2) */
/* G0  : extraterrestrial global solar irradiation (on an horizontal plane)
   =B0*/
/* G0h : hourly extraterrestrial solar irradiation (on an horizontal plane) */
/* G0d : daily extraterrestrial solar irradiation (on an horizontal plane) */

/* NB : All angles are computed in radians as a standard.
        The basic trigonometric calculations on the position of the sun are 
	carried out in LAT. */

        /* Source : */
        /* Inputs :
           phi_g : latitude of site (in radians, positive to North)
           delta : solar declination angle (in radians)
           omega : solar hour angle (in radians) */
        /* Outputs :
           gamma : solar altitude angle (in radians)
           theta : solar zenithal angle (in radians) */
        /* The procedure "elevation_zenith_sun" computes the solar elevation (or
           altitude) angle and the solar zenithal (or incidence) angle. These two
           angles are complementary. Returns 0 if OK, 1 otherwise. */

int spa_calculate(spa_data *sp)
{
    int result,res,julian_day;
    double delta,omega,lat,lon,gamma,alpha,t,theta,
           omega_sr,omega_ss;

    result = validate_inputs(sp);

    if (result == 0)
    {
        lat   = sp->latitude * Pi/180;
        lon   = sp->longitude* Pi/180;
        t     = sp->hour + sp->minute/60 + sp->second/3600;

        res = make_julian_day(sp->day,sp->month,sp->year,julian_day);
        printf("MYSPA Julian %d",res);
        res *= declination_sun(sp->year,julian_day,lon,delta);
        sp->delta_prime = delta;
        printf("MYSPA Declination %d",res);
        res *= sunrise_hour_angle(lat,delta,-1,omega_sr,omega_ss);
        sp->srha = omega_sr;
        sp->ssha = omega_ss;
        printf("MYSPA Sunrise %d",res);
        res *= solar_hour_angle(t,omega);
        printf("MYSPA HA%d",res);
        res *= elevation_zenith_sun(lat,delta,omega,gamma,theta);
        printf("MYSPA Elevation %d",res);
        sp->zenith  = gamma * 180/Pi;

        res *= azimuth_sun(lat,delta,omega,gamma,alpha);
        printf("MYSPA Azi %d",res);
        sp->azimuth = alpha * 180/Pi;

        sp->azimuth180 = sp->azimuth + 180;
    }
    return result;
}
	
/*********************************************/
/*                                           */
/* G E O M E T R Y  O F  S O L A R  B E A M, */
/*                                           */
/* A  N E A R  P O I N T  S O U R C E        */
/*                                           */
/*********************************************/

/********************/
/* BASIC PARAMETERS */
/********************/

int make_julian_day(day_of_month,month_number,year_number,julian_day)
int day_of_month,month_number,year_number,*julian_day;
/* Source : */
/* Inputs :
   day_of_month : day of the month (1..31)
   month_number : month number (1..12)
   year_number  : year number (4 digits) */
/* Outputs :
   julian_day : integer day number or julian day (1..366)
   */
/* The procedure "make_julian_day" converts a day given in day, month and year 
   into a julian day. Returns 0 if OK, 1 otherwise. */ 
{
 static int tab[12]={0,31,59,90,120,151,181,212,243,273,304,334};
 int ier,julien;

 ier = 1;
 if( (day_of_month > 0) && (day_of_month < 32) && (month_number > 0) && 
     (month_number < 13) && (year_number > 0) )  
  {
   ier = 0;
   julien = day_of_month + tab[month_number-1];
   if( ( ( ((year_number%4) == 0) && ((year_number%100) != 0) ) || 
	 ((year_number%400) == 0) ) && (month_number > 2) )  /* leap year */ 
     julien = julien + 1;
   *julian_day = julien;
  }
 return(ier);
}

int julian_to_date(year_number,julian_day,day_of_month,month_number)
int year_number,julian_day,*day_of_month,*month_number;
/* Source : MA in /u2/tm/src/srcgeo/julian_lib/ */
/* Inputs :
   year_number : year number (4 digits)
   julian_day  : integer day number or julian day (1..366)
   */
/* Outputs :
   day_of_month : day of the month (1..31)
   month_number : month number (1..12) */
/* The procedure "julian_to_date" does the reverse operation of the procedure 
   "make_julian_day" i.e. computes the month number and the respective day of 
   month from the information on year and integer day number. Returns 0 if OK,
   1 otherwise. */
{
 int tab[12]={0,31,59,90,120,151,181,212,243,273,304,334};
 int ier,m,jmax=365;

 ier = 1;
 if( ( ((year_number%4) == 0) && ((year_number%100) != 0) ) || 
     ((year_number%400) == 0) )  /* leap year */ 
  {
   jmax = jmax + 1;
   for(m=0;m<12;m++)
    {
     if(m > 1) tab[m] = tab[m] + 1;
    }
  }

 if( (julian_day > 0) && (julian_day <= jmax) && (year_number > 0) )
  {
   ier = 0;
   for(m=0;m<12;m++)
    {
     if( (julian_day > tab[m]) && (julian_day <= tab[m+1]) )
      {
       *month_number = m + 1;
       *day_of_month = julian_day - tab[m];
       break;
      }
     else
      if(julian_day > tab[11])
       {
	*month_number = 12;
	*day_of_month = julian_day - tab[11];
	break;
       }
    }
  }

 return(ier);
}

int nbdays_month(year_number,month_number,number_days_month)
int year_number,month_number,*number_days_month;
/* Source : */
/* Inputs :
   year_number  : year number (4 digits)
   month_number : month number (1..12) */
/* Outputs :
   number_days_month : number of days in a month */
/* The procedure "nbdays_month" gives the number of days in a month, useful for
   monthly calculations. Returns 0 if OK, 1 otherwise. */
{
 int tab_nbdays[12]={31,28,31,30,31,30,31,31,30,31,30,31};
 int ier;

 ier = 1;
 if( (year_number > 0) && (month_number > 0) && (month_number < 13) )
  {
   ier = 0;
   *number_days_month = tab_nbdays[month_number-1];
   if( ( ( ((year_number%4) == 0) && ((year_number%100) != 0) ) || 
	 ((year_number%400) == 0) ) && (month_number == 2) )  /* leap year */ 
     *number_days_month = *number_days_month + 1;
  }
 return(ier);
}

int number_to_name_month(month_number,month_name)
int month_number;
char month_name[4];
/* Source : */
/* Inputs :
   month_number : month number (1..12)
   month_name   : name of month (3 characters only, jan..dec) */
/* Outputs :
   month_name : name of the month abbreviated with 3 characters (jan..dec) */
/* The procedure "number_to_name_month" converts the month number into the 
   corresponding month name. Returns 0 if OK, 1 otherwise. */ 
{
 static char tab_name[][4]={"   ","jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
 int ier;
 
 ier = 1;
 if( (month_number > 0) && (month_number < 13) )
  {
   ier = 0;
   sprintf(month_name,"%s",tab_name[month_number]);
  }

 return(ier);
}

int Day_Angle(julian_day,day_angle)
int julian_day;
double *day_angle;
/* Source : */
/* Inputs :
   julian_day : integer day number or julian day (1..366) */
/* Outputs :
   day_angle : day angle (in radians) */
/* The procedure "Day_Angle" expresses the integer day number as an angle (in
   radians) from 12:00 hours on the day 31st December. A year length of 
   365.2422 days is used. Returns 0 if OK, 1 otherwise. */ 
{
 int ier;

 ier = 1;
 if( (julian_day > 0) && (julian_day <= 366) )
  {
   ier = 0;
   *day_angle = (double)julian_day * 2.0 * Pi / 365.2422;
  }
 return(ier);
}

int declination_sun(year_number,julian_day,lambda,delta)
int year_number,julian_day;
double lambda,*delta;
/* Sources : 
   Bourges, B., 1985. Improvement in solar declination computation. Solar 
   Energy, 35 (4), 367-369. 
   Carvalho, M.J. and Bourges, B., 1986. Program Eufrad 2.0 - User's Guide. 
   Project EUFRAT final scientific report, Contract EN3S-0111-F, Solar Energy 
   and Development in the European Community, pp. 12.1-12.74.
   Duffie, J.A. and Beckman, W.A., 1980. Solar Engineering of Thermal 
   Processes. Wiley-Interscience, New York. */
/* Inputs :
   year_number : year number (4 digits)
   julian_day  : integer day number or julian day (1..366)
   lambda      : longitude (in radians, positive to East) */
/* Outputs :
   delta : solar declination angle at noon (in radians) */
/* The procedure "declination_sun" computes the solar declination at noon in 
   solar time (in radians). A single (average) value per day -at noon- is 
   adequate for pratical calculations. The noon declination depends on 
   longitude, as noon occurs earlier if longitude is East of Greenwich, and 
   later if it is West. The chosen algorithm uses 1957 as base year; it is 
   basically a truncated Fourier series with six harmonics. Returns 0 if OK, 1
   otherwise. */
{
 int ier;
 double b1,b2,b3,b4,b5,b6,b7;
 double w0,n0,t1,wt;

 b1 =  0.0064979;
 b2 =  0.4059059;
 b3 =  0.0020054;
 b4 = -0.0029880;
 b5 = -0.0132296;
 b6 =  0.0063809;
 b7 =  0.0003508;

 ier = 1;
 /* n0 : spring-equinox time expressed in days from the beginning of the year 
    i.e. the time in decimal days elapsing from 00:00 hours Jan 1st to the 
    spring equinox at Greenwich in a given year */
 /* t1 : time in days, from the spring equinox */
 /* 0.5 represents the decimal day number at noon on Jan 1st at Greenwich */
 n0 = 78.8946 + 0.2422*(year_number-1957) - (int)(0.25*(year_number-1957));
 t1 = - 0.5 - lambda / (2 * Pi) - n0;
 w0 = 2 * Pi / 365.2422;
 if( (julian_day > 0) && (julian_day <= 366) )
  {
   ier = 0;
   wt = w0 * (julian_day + t1);
  }

 *delta = b1 + b2 * sin(wt) + b3 * sin(2 * wt) + b4 * sin(3 * wt) 
             + b5 * cos(wt) + b6 * cos(2 * wt) + b7 * cos(3 * wt);
 return(ier);
}

int declination_sun_month(month_number,type_use,delta_month)
int month_number,type_use;
double *delta_month;
/* Source : Gruter (Ed.) (1984) */
/* Inputs :
   month_number : month number (1..12) */
/* Outputs :
   delta_month : solar declination angle (in radians) */
/* The procedure "declination_sun_month" computes the noon solar declination 
   (in radians) in solar time, with a simplified form, in two cases:
   type_use=0 : for estimating monthly mean global solar radiation
   type_use=1 : for estimating monthly mean maximum global solar radiation
   The integer day number to be selected in each case for the computations is
   given by two tables. Returns 0 if OK, 1 otherwise. */
{
 const double deg_rad = (Pi/180.0); /* converts decimal degrees into radians*/
 int tab_julian_day[12]={17,46,75,105,135,162,198,228,259,289,319,345};
 int tab_julian_day_max[12]={29,57,89,119,150,173,186,217,248,278,309,339};
 int ier,julian_day;
 double day_angle,jm,c1,c2,c3,c4;

 ier = 1;
 if((type_use >= 0) && (type_use < 2))
  {
   if(type_use == 0)
     julian_day = tab_julian_day[month_number-1];
   if(type_use == 1)
     julian_day = tab_julian_day_max[month_number-1];
   ier = 0;
  }

 ier = Day_Angle(julian_day,&day_angle);
 if(ier != 0) return(ier);
 jm = day_angle;
 c1 = 0.3978;
 c2 = 80.2 * deg_rad;  /* 1.4000 in SSA manual */
 c3 = 1.92 * deg_rad;  /* 0.0355 in SSA manual */
 c4 = 2.80 * deg_rad;  /* 0.0489 in SSA manual */

 *delta_month = asin( c1 * sin(jm - c2 + c3 * sin(jm - c4)) );
 return(ier);
}

int solar_hour_angle(t,omega)
double t,*omega;
/* Source : */
/* Inputs :
   t : solar time i.e. LAT (0..24 decimal hours) */
/* Outputs :
   omega : solar hour angle (in radians) */
/* The procedure "solar_hour_angle" supplies the solar hour angle (in radians).
   By convention the hour angle is negative before noon and positive after noon
   Returns 0 if OK, 1 otherwise. */
{
 int ier;

 ier = 1;
 if((t >= 0.0) && (t <= 24.0))
  {
   ier = 0;
   *omega = (t - 12.0) * Pi / 12.0;
  }
 return(ier);
}

int omega_to_LAT(omega,t)
double omega,*t;
/* Source : */
/* Inputs :
   omega : solar hour angle (in radians) */
/* Outputs :
   t : solar time i.e. LAT (0..24 decimal hours) */
/* The procedure "omega_to_LAT" does the reverse operation of the procedure 
   "solar_hour_angle" i.e. computes the solar time (in decimal hours) from the 
   solar hour angle (in radians). Returns 0 if OK, 1 otherwise. */
{
 int ier;

 ier = 1;

 if((omega >= -Pi) && (omega <= Pi))
  {
   ier = 0;
   *t = 12.0 * (1.0 + omega / Pi);
  }
 return(ier); }

double geogr_to_geoce(phi_g)
double phi_g;
{
 double phi;
 double CC=0.99330552; /* Correction factor for converting geographic */
                       /* into geocentric latitude. CC=(Rpole/Requator)**2 */
                       /* Rpole=6356.752, Requator=6378.137 */
 if((phi_g>=-(Pi/2.0-0.0002)) || (phi_g<=(Pi/2.0-0.0002)))
   phi=atan(tan(phi_g)*CC);
 else
   phi=phi_g;
 return(phi);
}


int solar_hour_angle_h(phi_g,delta,t,omega)
double phi_g,delta,t,*omega;
/* Source : */
/* Inputs :
   phi_g : latitude (in radians, positive to North)
   delta : solar declination angle (in radians)
   t     : solar time i.e. LAT (0..24 decimal hours) */
/* Outputs :
   omega : solar hour angle (in radians) */
/* The procedure "solar_hour_angle_h" supplies an average value of the solar 
   hour angle (in radians) for a whole solar hour, taking into account only the
   portion of the solar hour with the sun standing above the horizon. Returns 0
   if OK, 1 otherwise. */
{
 int ier;
 double omega_sr,omega_ss,omega1,omega2;

 ier = 1;
 ier = sunrise_hour_angle(phi_g,delta,0.0,&omega_sr,&omega_ss);
 if(ier != 0) return(ier);
 
 omega1 = (t - 1.0 - 12.0) * Pi / 12.0;
 if(omega1 < omega_sr)
   omega1 = omega_sr;
 omega2 = (t - 12.0) * Pi / 12.0;
 if(omega2 > omega_ss)
   omega2 = omega_ss;

 *omega = (omega1 + omega2) / 2.0;

 return(ier);
}

/*********************************/
/* SUNRISE, SUNSET AND DAYLENGTH */
/*********************************/

int sunrise_hour_angle(phi_g,delta,gamma_riset,omega_sr,omega_ss)
double phi_g,delta,gamma_riset,*omega_sr,*omega_ss;
/* Source : */
/* Inputs :
   phi_g       : latitude of site (in radians, positive to North)
   delta       : solar declination angle (in radians)
   gamma_riset : solar elevation near sunrise/sunset:
                 - set to  0.0 for astronomical sunrise/sunset
	         - set to -1.0 for refraction corrected sunrise/sunset. */
/* Outputs :
   omega_sr : sunrise solar hour angle (in radians)
   omega_ss : sunset solar hour angle (in radians) */
/* The procedure "sunrise_hour_angle" supplies the sunrise and sunset hour 
   angles (in radians). Due to the dimension of the solar disk and the effect 
   of the atmospheric refraction, the edge of the solar disk will just appear 
   (disappear) at the horizon at sunrise (at sunset) when the calculated 
   astronomical elevation is 50'. Returns 0 if OK, 1 otherwise. */
{
 const double deg_rad = (Pi/180.0); /* converts decimal degrees into radians*/
 int ier;
 double horizon,max_delta,cos_omegas,omegas;
 double phi;

 ier = 1;
 if( (gamma_riset == 0.0) || (gamma_riset == -1.0) )
   ier = 0;
 horizon = (-50.0 / 60.0) * deg_rad;  /* horizon, -50' in radians */ 
 if(gamma_riset >= horizon)
   horizon = gamma_riset;
 
 phi=geogr_to_geoce(phi_g);
 max_delta = 23.45 * deg_rad;
 if( (fabs(phi) < (Pi/2.0)) && (fabs(delta) <= max_delta) && (ier == 0) )
  {
   cos_omegas = (sin(horizon) - (sin(phi) * sin(delta))) / 
                (cos(phi) * cos(delta));
   ier = 0;
  }
 else
   ier = 1;

 if(fabs(cos_omegas) < 1.0)
   omegas = acos(cos_omegas);
 if(cos_omegas >= 1.0)  /* the sun is always below the horizon : polar night */
   omegas = 0.0;
 if(cos_omegas <= -1.0)  /* the sun is always above the horizon : polar day */
   omegas = Pi;

 *omega_sr = -omegas;
 *omega_ss =  omegas;
 return(ier);
}

int timerise_daylength(omega_sr,omega_ss,t_sr,t_ss,S0)
double omega_sr,omega_ss,*t_sr,*t_ss,*S0;
/* Source : */
/* Inputs :
   omega_sr : sunrise hour angle (in radians)
   omega_ss : sunset hour angle (in radians) */
/* Outputs :
   t_sr : time of astronomical sunrise (in decimal hours)
   t_ss : time of astronomical sunset (in decimal hours)
   S0   : astronomical daylength (in decimal hours) */
/* The procedure "timerise_daylength" supplies the times of astronomical 
   sunrise and sunset, and the astronomical daylength, all in LAT decimal 
   hours. Returns 0 if OK, 1 otherwise. */
{
 int ier;

 ier = 1;
 if( (omega_sr >= -Pi) && (omega_sr <= 0.0) &&
     (omega_ss >= 0.0) && (omega_ss <= Pi) )
  {
   ier = 0;
   /* alternative way */
   /*
   ier = omega_to_LAT(omega_sr,&t_sr);
   if(ier == 0) ier == omega_to_LAT(omega_ss,&t_ss);
   if(ier != 0) return(ier);
   */
   *t_sr = 12.0 + omega_sr * 12.0 / Pi;
   *t_ss = 12.0 + omega_ss * 12.0 / Pi;
   *S0 = *t_ss - *t_sr;
  }
 return(ier);
}

/****************************/
/* CHANGING THE TIME SYSTEM */
/****************************/

int LMT_to_LAT(day_angle,lambda,lambda_ref,summer_corr,dt)
double day_angle,lambda,lambda_ref,*dt;
int summer_corr;
/* Source : Gruter (ed.) (1984) */
/* Inputs :
   day_angle   : day angle (in radians)
   lambda      : longitude of the site (in radians, positive to East)
   lambda_ref  : reference longitude of the time zone (in radians)
   summer_corr : correction for summer time (integer hours) */
/* Outputs :
   dt : Offset between local mean time (LMT) and local apparent time (LAT) (in 
   decimal hours) */
/* The procedure "LMT_to_LAT computes the difference (in decimal hours) between
   the LAT (local apparent time) and the LMT (local mean time or clock time) 
   systems at solar noon. Two stages:
   - the first stage calculates the equation of time, ET, wich allows for 
   perturbations in the rotational and angular orbital speed of the Earth.
   - the second stage handles the difference between the longitude of the site 
   under consideration and the reference time zone longitude for the site. A 
   summer time correction must be added for some countries.
   Returns 0 if OK, 1 otherwise. */ 
{
 const double deg_rad = (Pi/180.0); /* converts decimal degrees into radians*/
 int ier;
 double a1,a2,a3,a4,ET;

 ier = 1;
 a1 = -0.128;
 a2 = -0.165;
 a3 =  2.80 * deg_rad;
 a4 = 19.70 * deg_rad;
 if( (day_angle > 0.0) && (day_angle < (2.0*Pi*1.0021)) && 
     (fabs(lambda) <= Pi) && (fabs(lambda_ref) <= Pi) )
  {
   ier = 0;
   ET = a1 * sin(day_angle - a3) + a2 * sin(2.0 * day_angle + a4);
   *dt = ET + ((lambda - lambda_ref) * 12.0 / Pi) - (double)summer_corr;
  }

 return(ier);
}

int UT_to_LAT(UT,day_angle,lambda,LAT)
double UT,day_angle,lambda,*LAT;
/* Source : */
/* Inputs :
   UT          : Universal Time (in decimal hours)
   day_angle   : day angle (in radians)
   lambda      : longitude of the site (in radians, positive to East) */
/* Outputs :
   LAT : local apparent time or solar time or true solar time (TST) (in decimal
         hours) */
/* The procedure "UT_to_LAT computes the conversion of the UT (Universal time) 
   into the LAT (local apparent time) systems at solar noon (in decimal hours).
   First, the equation of time, ET, is computed (in decimal hours), wich allows
   for perturbations in the rotational and angular orbital speed of the Earth.
   Returns 0 if OK, 1 otherwise. */ 
{
 const double deg_rad = (Pi/180.0); /* converts decimal degrees into radians*/
 int ier;
 double a1,a2,a3,a4,ET;

 ier = 1;
 a1 = -0.128;
 a2 = -0.165;
 a3 =  2.80 * deg_rad;
 a4 = 19.70 * deg_rad;
 if( (UT >= 0.0) && (UT <= 24.0) && (day_angle > 0.0) && 
     (day_angle < (2.0*Pi*1.0021)) && (fabs(lambda) <= Pi) )
  {
   ier = 0;
   ET = a1 * sin(day_angle - a3) + a2 * sin(2.0 * day_angle + a4);
  *LAT = UT + ET + (lambda * 12.0 / Pi);
  if(*LAT<0) *LAT+=24.0;
  if(*LAT>24.0) *LAT-=24.0;
  }

 return(ier);
}

/**********************************/
/* POSITION OF THE SUN IN THE SKY */
/**********************************/

int elevation_zenith_sun(phi_g,delta,omega,gamma,theta)
double phi_g,delta,omega,*gamma,*theta;
/* Source : */
/* Inputs :
   phi_g : latitude of site (in radians, positive to North)
   delta : solar declination angle (in radians)
   omega : solar hour angle (in radians) */
/* Outputs :
   gamma : solar altitude angle (in radians)
   theta : solar zenithal angle (in radians) */
/* The procedure "elevation_zenith_sun" computes the solar elevation (or 
   altitude) angle and the solar zenithal (or incidence) angle. These two 
   angles are complementary. Returns 0 if OK, 1 otherwise. */
{
 int ier;
 double omega_sr,omega_ss;
 double phi;

 ier = 1;
 phi=geogr_to_geoce(phi_g);
 ier = sunrise_hour_angle(phi_g,delta,0.0,&omega_sr,&omega_ss);
 if(ier != 0) return(ier);
 if((omega < omega_sr) || (omega > omega_ss))
   *gamma = 0.0;
 else
   *gamma = asin( sin(phi) * sin(delta) + cos(phi) * cos(delta) * cos(omega) );
 if(*gamma < 0.0)
   *gamma = 0.0;

 *theta = (Pi / 2.0) - *gamma;

 return(ier);
}

int azimuth_sun(phi_g,delta,omega,gamma,alpha)
double phi_g,delta,omega,gamma,*alpha;
/* Source : */
/* Inputs :
   phi_g : latitude of site (in radians, positive to North)
   delta : solar declination angle (in radians)
   omega : solar hour angle (in radians)
   gamma : solar altitude angle (in radians) */
/* Outputs :
   alpha : solar azimuthal angle (in radians) */
/* The procedure "azimuth_sun" computes the solar azimuth angle in the Northern
   hemisphere. The azimuth angle has a positive value when the sun is to the 
   west of South, i.e. during the afternoon in solar time. For the Southern 
   hemisphere, the azimuth angle is measured from North. Returns 0 if OK, 1 
   otherwise. */
{
 int ier;
 double cos_as,sin_as,x;
 double phi;

 ier = 0;
 phi=geogr_to_geoce(phi_g);
 cos_as = (sin(phi) * sin(gamma) - sin(delta)) / (cos(phi) * cos(gamma));
 if(phi < 0.0) cos_as = -cos_as;   /* Southern hemisphere */
 sin_as = cos(delta) * sin(omega) / cos(gamma);
 x = acos(cos_as);
 if(fabs(x) > Pi) ier = 1;
 if(sin_as >= 0.0)
   *alpha =  x;
 else
   *alpha = -x;
   
 return(ier);
}

/********************************/
/* EXTRATERRESTRIAL IRRADIATION */
/********************************/

int corr_distance(day_angle,eccentricity)
double day_angle,*eccentricity;
/* Source : Gruter (ed.) (1984) */
/* Inputs :
   day_angle : day angle (in radians) */
/* Outputs :
   eccentricity : correction for Earth orbit eccentricity */
/* The procedure "corr_distance" computes the correction for the variation of 
   sun-earth distance from its mean value (also known as eccentricity). It is a
   fucntion of time, but a single (average) value per day is enough for 
   practical calculations. Returns 0 if OK, 1 otherwise. */ 
{
 const double deg_rad = (Pi/180.0); /* converts decimal degrees into radians*/
 int ier;
 double a;

 ier = 1;
 a = 2.80 * deg_rad;
 if( (day_angle >= 0.0) && (day_angle <= (2.0*Pi*1.0021)) )
  {
   ier = 0;
   *eccentricity = 1.0 + 0.03344 * cos(day_angle - a);
  }
 return(ier);
}

int G0_normal(I0j,theta,G0)
double I0j,theta,*G0;
/* Source : */
/* Inputs :
   IOj : extraterrestrial solar irradiance normal to beam for day j; I0j=I0*fj
   theta : solar incidence angle or solar zenithal angle */
/* Outputs :
   G0 : extraterrestrial global solar irradiation (in Wh/m2) */
/* The procedure "G0_normal" delivers the extraterrestrial solar irradiance 
   normal to beam for day j. Returns 0 if OK, 1 otherwise. */
{
 *G0 = I0j * cos(theta);
 return 0;
}

int G0_general(phi_g,eccentricity,delta,omega1,omega2,G0_12)
double phi_g,eccentricity,delta,omega1,omega2,*G0_12;
/* Source : */
/* Inputs :
   phi_g        : latitude of site (in radians, positive to North)
   eccentricity : correction for Earth orbit eccentricity
   delta        : solar declination angle (in radians)
   omega1       : solar hour angle at beginning of the period (in radians)
   omega2       : solar hour angle at end of the period (in radians) */
/* Outputs :
   G0_12 : extraterrestrial solar irradiation (in Wh/m2) */
/* The procedure "G0_general" delivers the extraterrestrial solar irradiation 
   incident on an horizontal surface in the general case (in Wh/m2). Returns 0
   if OK, 1 otherwise */
{
 int ier;
 double omega_sr,omega_ss,a,b1,b2,c;
 double phi;

 ier = 1;
 phi=geogr_to_geoce(phi_g);
 ier = sunrise_hour_angle(phi_g,delta,0.0,&omega_sr,&omega_ss);
 if(ier != 0) return(ier);
 if(omega1 < omega_sr)
   omega1 = omega_sr;
 if(omega2 < omega_sr)
   omega2 = omega_sr;
 if(omega1 > omega_ss)
   omega1 = omega_ss;
 if(omega2 > omega_ss)
   omega2 = omega_ss;
      
 if(omega2 <= omega1)
   *G0_12 = 0.0;
 else
  {
   a = I0 * eccentricity * Dl / (2.0 * Pi);
   b1 = sin(phi) * sin(delta) * (omega2 - omega1);
   b2 = cos(phi) * cos(delta) * (sin(omega2) - sin(omega1));
   c = a * (b1 + b2);
   if(c < 0.0)
     *G0_12 = 0.0;
   else
     *G0_12 = c;
  }

 return(ier);
}

int G0_day(phi_g,eccentricity,delta,G0d)
double phi_g,eccentricity,delta,*G0d;
/* Source : */
/* Inputs :
   phi_g        : latitude of site (in radians, positive to North)
   eccentricity : correction for Earth orbit eccentricity
   delta        : solar declination angle (in radians) */
/* Outputs :
   G0d : daily extraterrestrial solar irradiation (in Wh/m2) */
/* The procedure "G0_day" delivers the extraterrestrial solar irradiation 
   incident on an horizontal surface in case of daily values (in Wh/m2), i.e.
   omega1 = omega_sr = -omega_ss  et omega2 = omega_ss. Returns 0 if OK, 1 
   otherwise.
   REMARK: It is a special case of G0_general with the sunrise and sunset 
   angles as integration limits. */
{
 int ier;
 double omega_sr,omega_ss,a,b;
 double phi;

 ier = 1;
 phi=geogr_to_geoce(phi_g);
 ier = sunrise_hour_angle(phi_g,delta,0.0,&omega_sr,&omega_ss);
 if(ier != 0) return(ier);
 a = I0 * eccentricity * Dl / Pi;
/* b = cos(phi) * cos(delta) * (sin(omega_ss) - omega_ss * cos(omega_ss));*/
 b = sin(phi)*sin(delta)*omega_ss + cos(phi)*cos(delta)*sin(omega_ss);
 *G0d = a * b;
 
 return(ier);
}

int G0_hours_profile(phi_g,eccentricity,delta,G0h)
double phi_g,eccentricity,delta,G0h[];
/* Source : */
/* Inputs :
   phi_g        : latitude of site (in radians, positive to North)
   eccentricity : correction for Earth orbit eccentricity
   delta        : solar declination (in radians) */
/* Outputs :
   G0h[1..24] : 24 hourly extraterrestrial solar irradiation (in Wh/m2) */
/* The procedure "G0_hours_profile" delivers the extraterrestrial solar 
   irradiation incident on an horizontal surface in case of hourly values, for
   the 24 integral hours in a given day (in Wh/m2), i.e. |omega1-omega2| = 
   Pi/12. Returns 0 if OK, 1 otherwise */
{
 int ier,i;
 double omega_sr,omega_ss,a,b1,b2;
 double phi;
 double t1,t2,omega1,omega2;

 ier = 1;
 phi=geogr_to_geoce(phi_g);
 ier = sunrise_hour_angle(phi_g,delta,0.0,&omega_sr,&omega_ss);
 if(ier != 0) return(ier);
 a = I0 * eccentricity * Dl / (2.0 * Pi);
 b1 = sin(phi) * sin(delta);
 b2 = cos(phi) * cos(delta);

 for(i=0;i<24;i++)
  {
   t1 = (double)(i+1) - 1.0;
   ier = solar_hour_angle(t1,&omega1);
   if(ier != 0) return(ier);
   t2 = (double)(i+1);
   ier = solar_hour_angle(t2,&omega2);
   if(ier != 0) return(ier);
   
   if((omega2 < omega_sr) || (omega1 > omega_ss))
     G0h[i] = 0.0;
   else
    {
     if(omega1 < omega_sr)
       omega1 = omega_sr;
     if(omega2 > omega_ss)
       omega2 = omega_ss;
     G0h[i] = a * (b1 * (omega2 - omega1) + b2 * (sin(omega2) - sin(omega1)));
    }
  }

 return(ier);
}

int G0_hour(phi_g,eccentricity,delta,t,G0h)
double phi_g,eccentricity,delta,t,*G0h;
/* Source : */
/* Inputs :
   phi_g        : latitude of site (in radians, positive to North)
   eccentricity : correction for Earth orbit eccentricity
   delta        : solar declination (in radians)
   t            : solar time i.e. LAT (0..24 decimal hours) */
/* Outputs :
   G0h : hourly extraterrestrial solar irradiation (in Wh/m2) */
/* The procedure "G0_hour" delivers the extraterrestrial solar irradiation 
   incident on an horizontal surface for a specific hour in a given day (in 
   Wh/m2), i.e. |omega1-omega2| = Pi/12. t is taken as the mid hour for 
   computation of the hourly value of extraterrestrial solar irradiation. 
   Returns 0 if OK, 1 otherwise */
{
 int ier;
 double omega_sr,omega_ss,a,b1,b2;
 double t1,t2,omega1,omega2;
 double phi;

 ier = 1;
 phi=geogr_to_geoce(phi_g);
 ier = sunrise_hour_angle(phi_g,delta,0.0,&omega_sr,&omega_ss);
 if(ier != 0) return(ier);
 a = I0 * eccentricity * Dl / (2.0 * Pi);
 b1 = sin(phi) * sin(delta);
 b2 = cos(phi) * cos(delta);

 t1 = t - 1.0;
 ier = solar_hour_angle(t1,&omega1);
 if(ier != 0) return(ier);
 t2 = t;
 ier = solar_hour_angle(t2,&omega2);
 if(ier != 0) return(ier);
 
 if(omega1 < omega_sr)
   omega1 = omega_sr;
 if(omega2 < omega_sr)
   omega2 = omega_sr;
 
 if(omega2 <= omega1)
   *G0h = 0.0;
 else
  {
   *G0h = a * (b1 * (omega2 - omega1) + b2 * (sin(omega2) - sin(omega1)));
   if(*G0h < 0.0)
     *G0h = 0.0;
  }

 return(ier);
}

/***********************************************/
/* MONTHLY AVERAGES OF SOLAR INPUTS PARAMETERS */
/***********************************************/
int monthly_averages(month_number,year_number,phi_g,lambda,gamma_riset,day_angle_m,delta_m,omega_ss_m,S0_m,eccentricity_m,G0d_m,G0h_m)
int month_number,year_number;
double phi_g,lambda,gamma_riset;
double *day_angle_m,*delta_m,*omega_ss_m,*S0_m,*eccentricity_m,*G0d_m,G0h_m[];
/* Source : */
/* Inputs :
   month_number : month number (1..12)
   year_number  : year number (4 digits)
   phi_g        : latitude of site (in radians, positive to North)
   lambda       : longitude of site (in radians, positive to East)
   gamma_riset  : solar elevation near sunrise/sunset:
                  - set to  0.0 for astronomical sunrise/sunset
		  - set to -1.0 for refraction corrected sunrise/sunset. */
/* Outputs :        monthly average of...
   day_angle_m    : ... day angle (in radians)
   delta_m        : ... solar declination angle (in radians)
   omega_ss_m     : ... sunset hour angle (in radians)
   S0_m           : ... astronomical daylength (in decimal hours)
   eccentricity_m : ... eccentricity
   G0d_m          : ... daily extraterrestrial irradiation (in Wh/m2)
   G0h_m[1..24]   : ... 24 hourly extraterrestrial solar irradiation (in Wh/m2)
   */
/* The procedure "monthly_averages" computes directly the monthly average 
   values of solar parameters : day angle (in radians), eccentricity, 
   declination (in radians), sunset hour angle (in radians), daylength (in 
   decimal hours), daily extraterrestrial irradiation (in Wh/m2) and the 24 
   hourly extraterrestrial solar irradiation (in Wh/m2) . Returns 0 if OK, 1 
   otherwise */
{
 int ier,i,day_of_month,number_days_month,julian_day;
 double day_angle,delta,omega_sr,omega_ss,t_sr,t_ss,S0,eccentricity,G0d;
 double G0h[24];
 double nbd_m;

 /* Initialization */
 *day_angle_m = 0.0;
 *delta_m = 0.0;
 *omega_ss_m = 0.0;
 *S0_m = 0.0;
 *eccentricity_m = 0.0;
 *G0d_m = 0.0;
 for(i=0;i<24;i++)
   G0h_m[i] = 0.0;

 ier = 1;
 ier = nbdays_month(year_number,month_number,&number_days_month);
 if(ier != 0) return(ier);
 
 for(day_of_month=1;day_of_month<=number_days_month;day_of_month++)
  {
   ier = make_julian_day(day_of_month,month_number,year_number,&julian_day);
   if(ier == 0)
     ier = Day_Angle(julian_day,&day_angle);
   if(ier == 0)
     ier = declination_sun(year_number,julian_day,lambda,&delta);
   if(ier == 0)
     ier = sunrise_hour_angle(phi_g,delta,gamma_riset,&omega_sr,&omega_ss);
   if(ier == 0)
     ier = timerise_daylength(omega_sr,omega_ss,&t_sr,&t_ss,&S0);
   if(ier == 0)
     ier = corr_distance(day_angle,&eccentricity);
   if(ier == 0)
     ier = G0_day(phi_g,eccentricity,delta,&G0d);
   if(ier == 0)
     ier = G0_hours_profile(phi_g,eccentricity,delta,G0h);
   if(ier != 0) return(ier);

   /* OR */
   /* ier = solar_parameters_day(day_of_month,month_number,year_number,phi_g,lambda,gamma_riset,&day_angle,&delta,&omega_ss,&S0,&eccentricity,&G0d,G0h); */
   if(ier != 0) return(ier);

   /* REMARK: In the original procedure test on G0d: if(*G0d > 0) */
   *day_angle_m = *day_angle_m + day_angle;
   *delta_m = *delta_m + delta;
   *omega_ss_m = *omega_ss_m + omega_ss;
   *S0_m = *S0_m + S0; 
   *eccentricity_m = *eccentricity_m + eccentricity;
   *G0d_m = *G0d_m + G0d;
   for(i=0;i<24;i++)
     G0h_m[i] = G0h_m[i] + G0h[i];
  }

 nbd_m = (double)number_days_month;
 *day_angle_m = *day_angle_m / nbd_m;
 *delta_m = *delta_m / nbd_m;
 *omega_ss_m = *omega_ss_m / nbd_m;
 *S0_m = *S0_m / nbd_m;
 *eccentricity_m = *eccentricity_m / nbd_m;
 *G0d_m = *G0d_m / nbd_m;
 for(i=0;i<24;i++) 
   G0h_m[i] = G0h_m[i] / nbd_m;

 return(ier);
}

/****************************************************/
/* YEARLY AVERAGES OF MONTHLY SOLAR PARAMETERS      */
/* (LONG TERM MEANS OF MONTHLY MEANS OF DAILY SUMS) */
/****************************************************/
int yearly_averages(month_number,year_start,year_end,phi_g,lambda,gamma_riset,day_angle_y,delta_y,omega_ss_y,S0_y,eccentricity_y,G0d_y,G0h_y)
int month_number;
int year_start,year_end;
double phi_g,lambda,gamma_riset;
double *day_angle_y,*delta_y,*omega_ss_y,*S0_y,*eccentricity_y,*G0d_y,G0h_y[];
/* Source : */
/* Inputs :
   month_number : month number (1..12)
   year_start   : starting year of the considered period (4 digits)
   year_end     : ending year of the considered period (4 digits)
   phi_g        : latitude of site (in radians, positive to North)
   lambda       : longitude of site (in radians, positive to East)
   gamma_riset  : solar elevation near sunrise/sunset:
                  - set to  0.0 for astronomical sunrise/sunset
		  - set to -1.0 for refraction corrected sunrise/sunset. */
/* Outputs :        yearly average of...
   day_angle_y    : ... day angle (in radians)
   delta_y        : ... solar declination angle (in radians)
   omega_ss_y     : ... sunset hour angle (in radians)
   S0_y           : ... astronomical daylength (in decimal hours)
   eccentricity_y : ... eccentricity
   G0d_y          : ... daily extraterrestrial irradiation (in Wh/m2)
   G0h_y[1..24]   : ... 24 hourly extraterrestrial solar irradiation (in Wh/m2)
   */
/* The procedure "yearly_averages" computes directly the yearly average over a
   defined period of years of monthly average values of solar parameters : day 
   angle (in radians), eccentricity, declination (in radians), sunset hour 
   angle (in radians), daylength (in decimal hours), daily extraterrestrial 
   irradiation (in Wh/m2) and 24 hourly extraterrestrial solar irradiation 
   (in Wh/m2). Returns 0 if OK, 1 otherwise */
{
 int ier,i,year_number;
 double day_angle_m,delta_m,omega_ss_m,S0_m,eccentricity_m,G0d_m,G0h_m[24];
 double number_of_years;

 number_of_years = (double)(year_end - year_start + 1.);
 ier = 1;

 /* Initialization of parameters */
 *day_angle_y = 0.0;
 *delta_y = 0.0;
 *omega_ss_y = 0.0;
 *S0_y = 0.0;
 *eccentricity_y = 0.0;
 *G0d_y = 0.0;
 for(i=0;i<24;i++) 
   G0h_y[i] = 0.0;

 for(year_number=year_start;year_number<=year_end;year_number++)
  {
   ier = monthly_averages(month_number,year_number,phi_g,lambda,gamma_riset,&day_angle_m,&delta_m,&omega_ss_m,&S0_m,&eccentricity_m,&G0d_m,G0h_m);
   if(ier != 0) return(ier);
     
   *day_angle_y = *day_angle_y + day_angle_m;
   *delta_y = *delta_y + delta_m;
   *omega_ss_y = *omega_ss_y + omega_ss_m;
   *S0_y = *S0_y + S0_m; 
   *eccentricity_y = *eccentricity_y + eccentricity_m;
   *G0d_y = *G0d_y + G0d_m;
   for(i=1;i<=24;i++) 
     G0h_y[i] = G0h_y[i] + G0h_m[i];
   /*
   printf("year_number= %4d  G0d_m = %8.2f (Wh/m2)  G0d_y = %8.2f (Wh/m2)\n",year_number,G0d_m,*G0d_y);
   for(i=0;i<24;i++) 
     printf("hh= %2d (hours)\tG0h_m = %8.2f (Wh/m2)\tG0h_y = %8.2f (Wh/m2)\n",i+1,G0h_m[i],G0h_y[i]);
   */
  }

 *day_angle_y = *day_angle_y / number_of_years;
 *delta_y = *delta_y / number_of_years;
 *omega_ss_y = *omega_ss_y / number_of_years;
 *S0_y = *S0_y / number_of_years;
 *eccentricity_y = *eccentricity_y / number_of_years;
 *G0d_y = *G0d_y / number_of_years;
 for(i=0;i<24;i++)
   G0h_y[i] = G0h_y[i] / number_of_years;
      
 return(ier);
}

/*********************************************/
/* SOLAR INPUTS PARAMETERS FOR A CERTAIN DAY */
/*********************************************/
int solar_parameters_day(day_of_month,month_number,year_number,phi_g,lambda,gamma_riset,day_angle,delta,omega_ss,S0,eccentricity,G0d,G0h)
int day_of_month,month_number,year_number;
double phi_g,lambda,gamma_riset;
double *day_angle,*delta,*omega_ss,*S0,*eccentricity,*G0d,G0h[];
/* Source : */
/* Inputs :
   day_of_month : day of the month (1..31)
   month_number : month number (1..12)
   year_number  : year number (4 digits)
   phi_g        : latitude of site (in radians, positive to North)
   lambda       : longitude of site (in radians, positive to East)
   gamma_riset  : solar elevation near sunrise/sunset:
                  - set to  0.0 for astronomical sunrise/sunset
		  - set to -1.0 for refraction corrected sunrise/sunset. */
/* Outputs :
   day_angle    : day angle (in radians)
   delta        : solar declination angle (in radians)
   omega_ss     : sunset hour angle (in radians)
   S0           : astronomical daylength (in decimal hours)
   eccentricity : eccentricity
   G0d          : daily extraterrestrial irradiation (in Wh/m2)
   G0h[1..24]   : 24 hourly extraterrestrial solar irradiation (in Wh/m2)
   */
/* The procedure "solar_parameters_day" computes the solar geometry related 
   values for a certain day : day angle (in radians), eccentricity, 
   declination (in radians), sunset hour angle (in radians), daylength (in 
   decimal hours), daily extraterrestrial irradiation (in Wh/m2) and the 24 
   hourly extraterrestrial solar irradiation (in Wh/m2). Returns 0 if OK, 1 
   otherwise. 
   REMARK: gamma_riset set to 0.0 in the original procedure by Aguiar.*/
{
 int ier,i,julian_day;
 double omega_sr,t_sr,t_ss;

 ier = 1;
 ier = make_julian_day(day_of_month,month_number,year_number,&julian_day);
 if(ier == 0)
   ier = Day_Angle(julian_day,day_angle);
 if(ier == 0)
   ier = declination_sun(year_number,julian_day,lambda,delta);
 if(ier == 0)
   ier = sunrise_hour_angle(phi_g,*delta,gamma_riset,&omega_sr,omega_ss);
 if(ier == 0)
   ier = timerise_daylength(omega_sr,*omega_ss,&t_sr,&t_ss,S0);
 if(ier == 0)
   ier = corr_distance(*day_angle,eccentricity);
 if(ier == 0)
   ier = G0_day(phi_g,*eccentricity,*delta,G0d);
 if(ier == 0 && *G0d > 0.0)
   ier = G0_hours_profile(phi_g,*eccentricity,*delta,G0h);

 return(ier);
}

/******************************************************************/
/* SOLAR INPUTS PARAMETERS FOR MONTHLY AVERAGE IRRADIATION MODELS */
/******************************************************************/
int solar_parameters_avg(month_number,phi_g,gamma_riset,day_angle_avg,delta_avg,omega_ss_avg,S0_avg,eccentricity_avg,G0d_avg,G0h_avg)
int month_number;
double phi_g,gamma_riset;
double *day_angle_avg,*delta_avg,*omega_ss_avg,*S0_avg,*eccentricity_avg,
       *G0d_avg,G0h_avg[];
/* Source : */
/* Inputs :
   month_number : month number (1..12)
   phi_g        : latitude of site (in radians, positive to North)
   gamma_riset  : solar elevation near sunrise/sunset:
                  - set to  0.0 for astronomical sunrise/sunset
		  - set to -1.0 for refraction corrected sunrise/sunset. */
/* Outputs :        average ... for the given month
   day_angle_avg    : day angle (in radians)
   delta_avg        : solar declination angle (in radians)
   omega_ss_avg     : sunset hour angle (in radians)
   S0_avg           : astronomical daylength (in decimal hours)
   eccentricity_avg : eccentricity
   G0d_avg          : daily extraterrestrial irradiation (in Wh/m2)
   G0h_avg[1..24]   : 24 hourly extraterrestrial solar irradiation (in Wh/m2)
   */
/* The procedure "solar_parameters_acg" computes the solar geometry related 
   values for monthly average irradiation models : day angle (in radians), 
   eccentricity, declination (in radians), sunset hour angle (in radians), 
   daylength (in decimal hours), daily extraterrestrial irradiation (in Wh/m2) 
   and the 24 hourly extraterrestrial solar irradiation (in Wh/m2). Returns 0 
   if OK, 1 otherwise. 
   REMARK: gamma_riset set to 0.0 in the original procedure by Aguiar.*/
{
 int ier,i,julian_day;
 double omega_sr,t_sr,t_ss;

 /* recommended values of day number for estimating monthly mean global solar 
    radiation */
 int tab_julian_day[12]={17,46,75,105,135,162,198,228,259,289,319,345};
 int type_use;

 ier = 1;
 type_use = 0;  /* for estimating monthly mean global solar radiation */

 if((type_use >= 0) && (type_use < 2))
  {
   if(type_use == 0)
     julian_day = tab_julian_day[month_number-1];
   ier = 0;
  }
 if(ier == 0)
   ier = Day_Angle(julian_day,day_angle_avg);
 if(ier == 0)
   ier = declination_sun_month(month_number,type_use,delta_avg);
 if(ier == 0)
   ier = sunrise_hour_angle(phi_g,*delta_avg,gamma_riset,&omega_sr,omega_ss_avg);
 if(ier == 0)
   ier = timerise_daylength(omega_sr,*omega_ss_avg,&t_sr,&t_ss,S0_avg);
 if(ier == 0)
   ier = corr_distance(*day_angle_avg,eccentricity_avg);
 if(ier == 0)
   ier = G0_day(phi_g,*eccentricity_avg,*delta_avg,G0d_avg);
 if(ier == 0)
   ier = G0_hours_profile(phi_g,*eccentricity_avg,*delta_avg,G0h_avg);

 return(ier);
}

/******************************************************************/
/* SOLAR INPUTS PARAMETERS FOR MONTHLY MAXIMUM IRRADIATION MODELS */
/******************************************************************/
int solar_parameters_max(month_number,phi_g,gamma_riset,day_angle_max,delta_max,omega_ss_max,S0_max,eccentricity_max,G0d_max,G0h_max)
int month_number;
double phi_g,gamma_riset;
double *day_angle_max,*delta_max,*omega_ss_max,*S0_max,*eccentricity_max,
       *G0d_max,G0h_max[];
/* Source : */
/* Inputs :
   month_number : month number (1..12)
   phi_g        : latitude of site (in radians, positive to North)
   gamma_riset  : solar elevation near sunrise/sunset:
                  - set to  0.0 for astronomical sunrise/sunset
		  - set to -1.0 for refraction corrected sunrise/sunset. */
/* Outputs :        average ... for the given month
   day_angle_max    : day angle (in radians)
   delta_max        : solar declination angle (in radians)
   omega_ss_max     : sunset hour angle (in radians)
   S0_max           : astronomical daylength (in decimal hours)
   eccentricity_max : eccentricity
   G0d_max          : daily extraterrestrial irradiation (in Wh/m2)
   G0h_max[1..24]   : 24 hourly extraterrestrial solar irradiation (in Wh/m2)
   */
/* The procedure "solar_parameters_acg" computes the solar geometry related 
   values for monthly average irradiation models : day angle (in radians), 
   eccentricity, declination (in radians), sunset hour angle (in radians), 
   daylength (in decimal hours), daily extraterrestrial irradiation (in Wh/m2) 
   and the 24 hourly extraterrestrial solar irradiation (in Wh/m2). Returns 0 
   if OK, 1 otherwise. 
   REMARK: gamma_riset set to 0.0 in the original procedure by Aguiar.*/
{
 int ier,i,julian_day;
 double omega_sr,t_sr,t_ss;

 /* recommended values of day number for estimating monthly mean maximum 
    global solar radiation */
 int tab_julian_day_max[12]={29,57,89,119,150,173,186,217,248,278,309,339};
 int type_use;

 ier = 1;
 type_use = 1;  /* for estimating monthly mean global solar radiation */

 if((type_use >= 0) && (type_use < 2))
  {
   if(type_use == 1)
     julian_day = tab_julian_day_max[month_number-1];
   ier = 0;
  }
 if(ier == 0)
   ier = Day_Angle(julian_day,day_angle_max);
 if(ier == 0)
   ier = declination_sun_month(month_number,type_use,delta_max);
 if(ier == 0)
   ier = sunrise_hour_angle(phi_g,*delta_max,gamma_riset,&omega_sr,omega_ss_max);
 if(ier == 0)
   ier = timerise_daylength(omega_sr,*omega_ss_max,&t_sr,&t_ss,S0_max);
 if(ier == 0)
   ier = corr_distance(*day_angle_max,eccentricity_max);
 if(ier == 0)
   ier = G0_day(phi_g,*eccentricity_max,*delta_max,G0d_max);
 if(ier == 0)
   ier = G0_hours_profile(phi_g,*eccentricity_max,*delta_max,G0h_max);

 return(ier);
}

int validate_inputs(spa_data *spa)
{
    if ((spa->year        < -2000) || (spa->year        > 6000)) return 1;
    if ((spa->month       < 1    ) || (spa->month       > 12  )) return 2;
    if ((spa->day         < 1    ) || (spa->day         > 31  )) return 3;
    if ((spa->hour        < 0    ) || (spa->hour        > 24  )) return 4;
    if ((spa->minute      < 0    ) || (spa->minute      > 59  )) return 5;
    if ((spa->second      < 0    ) || (spa->second      > 59  )) return 6;

    if ((spa->hour        == 24  ) && (spa->minute      > 0   )) return 5;
    if ((spa->hour        == 24  ) && (spa->second      > 0   )) return 6;

    if (fabs(spa->delta_t)       > 8000    ) return 7;
    if (fabs(spa->timezone)      > 18      ) return 8;
    if (fabs(spa->longitude)     > 180     ) return 9;
    if (fabs(spa->latitude)      > 90      ) return 10;
    //if (fabs(spa->atmos_refract) > 5       ) return 16;
    if (     spa->elevation      < -6500000) return 11;



        if (fabs(spa->slope)         > 360) return 14;
        if (fabs(spa->azm_rotation)  > 360) return 15;


    return 0;
}

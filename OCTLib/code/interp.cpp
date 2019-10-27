/*******************************************************************************
*  $Id: interp.cpp 2 2010-01-05 03:34:41Z rosmir $
*  Copyright (C) 2006 Brian Bradie (bbradie@cnu.edu)
*  All rights reserved.
*  web-site: http://www.pcs.cnu.edu/~bbradie/cinterpolation.html
*  *****                              *******                              *****
*  Use of this source code is governed by a Clear BSD-style license that can be
*  found on the https://github.com/rosmir/octlab/blob/master/LICENSE web-page or
*  in the COPYRIGHT.TXT file
*******************************************************************************/

double neville ( int n, double *x, double *y, double t )

/*
     PURPOSE:
          evaluate the polynomial which interpolates a given
          set of data at a single value of the independent
          variable


     CALLING SEQUENCE:
          y = neville ( n, x, y, t );
          neville ( n, x, y, t );


     INPUTS:
          n		number of interpolating points
          x		array containing interpolating points
          y		array containing function values to
			be interpolated;  y[i] is the function
			value corresponding to x[i]
          t		value of independent variable at which
			the interpolating polynomial is to be
			evaluated


     OUTPUTS:
          y		value of interpolating polynomial defined
			by the data in the arrays x and y at the
			specified value of the independent variable
*/

{
     int i, j;
     double *f, fxbar;
     
     f = new double [n];
     for ( i = 0; i < n; i++ )
         f[i] = y[i];
     
     for ( j = 1; j < n; j++ )
         for ( i = n-1; i >= j; i-- ) {
             f[i] = ( (t-x[i-j])*f[i] - (t-x[i])*f[i-1] ) / ( x[i] - x[i-j] );
         }
        
     fxbar = f[n-1];
     delete [] f;     
     return ( fxbar );
}


double* divdiff ( int n, double *x, double *y )

/*
     PURPOSE:
          compute the coefficients of the Newton form of the 
	  polynomial which interpolates a given set of data


     CALLING SEQUENCE:
          coeff = divdiff ( n, x, y );
        

     INPUTS:
          n		number of interpolating points
          x		array containing interpolating points
          y		array containing function values to
			be interpolated;  y[i] is the function
			value corresponding to x[i]


     OUTPUTS:
          coeff		array containing the coefficients of the
			Newton form of the interpolating polynomial
			determined by the values in the arrays x
			and y

     REMARK:
          to evaluate Newton form of interpolating polynomial,
          use the routine 'nf_eval'
*/

{
     int i, j;
     double *f;
     
     f = new double [n];
     for ( i = 0; i < n; i++ )
         f[i] = y[i];
     
     for ( j = 1; j < n; j++ )
         for ( i = n-1; i >= j; i-- ) {
             f[i] = ( f[i] - f[i-1] ) / ( x[i] - x[i-j] );
         }
             
     return ( f );
}


double nf_eval ( int n, double *x, double *nf, double t )

/*
     PURPOSE:
          evaluate the Newton form of the polynomial which
          interpolates a given set of data at a single value of 
          the independent variable given the coefficients of
          the Newton form (obtained from 'divdiff')


     CALLING SEQUENCE:
          y = nf_eval ( n, x, nf, t );
          nf_eval ( n, x, nf, t );


     INPUTS:
          n		number of interpolating points
          x		array containing interpolating points
          nf		array containing the coefficients of 
			the Newton form of the interpolating
			polynomial (obtained from ÔdivdffÕ)
          t		value of independent variable at which
			the interpolating polynomial is to be
			evaluated


     OUTPUTS:
          y		value of interpolating polynomial at the
			specified value of the independent variable
*/

{
     int j;
     double temp;
     
     temp = nf[n-1];
     for ( j = n-2; j >= 0; j-- )
         temp = temp * ( t - x[j] ) + nf[j];
         
     return ( temp );
}


void tridiagonal ( int n, double *c, double *a, double *b, double *r )

{
     int i;
     
     for ( i = 0; i < n-1; i++ ) {
         b[i] /= a[i];
         a[i+1] -= c[i]*b[i];
     }
     
     r[0] /= a[0];
     for ( i = 1; i < n; i++ )
         r[i] = ( r[i] - c[i-1] * r[i-1] ) / a[i];
         
     for ( i = n-2; i >= 0; i-- )
         r[i] -= r[i+1] * b[i];
}


void cubic_nak ( int n, double *x, double *f, double *b, double *c, double *d )

/*
     PURPOSE:
          determine the coefficients for the 'not-a-knot'
          cubic spline for a given set of data


     CALLING SEQUENCE:
          cubic_nak ( n, x, f, b, c, d );


     INPUTS:
          n		number of interpolating points
          x		array containing interpolating points
          f		array containing function values to
			be interpolated;  f[i] is the function
			value corresponding to x[i]
          b		array of size at least n; contents will
			be overwritten
          c		array of size at least n; contents will
			be overwritten
          d		array of size at least n; contents will
			be overwritten


     OUTPUTS:
          b		coefficients of linear terms in cubic 
			spline
	  c		coefficients of quadratic terms in
			cubic spline
	  d		coefficients of cubic terms in cubic
			spline

     REMARK:
          remember that the constant terms in the cubic spline
          are given by the function values being interpolated;
          i.e., the contents of the f array are the constant
          terms

          to evaluate the cubic spline, use the routine
          'spline_eval'
*/
                    
{
     double *h,
            *dl,
            *dd,
            *du;
     int i;
     
     h  = new double [n];
     dl = new double [n];
     dd = new double [n];
     du = new double [n];
     
     for ( i = 0; i < n-1; i++ ) 
         h[i] = x[i+1] - x[i];
     for ( i = 0; i < n-3; i++ )
         dl[i] = du[i] = h[i+1];
     
     for ( i = 0; i < n-2; i++ ) {
         dd[i] = 2.0 * ( h[i] + h[i+1] );
         c[i]  = ( 3.0 / h[i+1] ) * ( f[i+2] - f[i+1] ) -
                 ( 3.0 / h[i] ) * ( f[i+1] - f[i] );
     }
     dd[0] += ( h[0] + h[0]*h[0] / h[1] );
     dd[n-3] += ( h[n-2] + h[n-2]*h[n-2] / h[n-3] );
     du[0] -= ( h[0]*h[0] / h[1] );
     dl[n-4] -= ( h[n-2]*h[n-2] / h[n-3] );
     
     tridiagonal ( n-2, dl, dd, du, c );
     
     for ( i = n-3; i >= 0; i-- )
         c[i+1] = c[i];
     c[0] = ( 1.0 + h[0] / h[1] ) * c[1] - h[0] / h[1] * c[2];
     c[n-1] = ( 1.0 + h[n-2] / h[n-3] ) * c[n-2] - h[n-2] / h[n-3] * c[n-3];
     for ( i = 0; i < n-1; i++ ) {
         d[i] = ( c[i+1] - c[i] ) / ( 3.0 * h[i] );
         b[i] = ( f[i+1] - f[i] ) / h[i] - h[i] * ( c[i+1] + 2.0*c[i] ) / 3.0;
     }
     
     delete [] h;
     delete [] du;
     delete [] dd;
     delete [] dl;
}


void cubic_clamped ( int n, double *x, double *f, double *b, double *c,
                     double *d, double fpa, double fpb )

/*
     PURPOSE:
          determine the coefficients for the clamped
          cubic spline for a given set of data


     CALLING SEQUENCE:
          cubic_clamped ( n, x, f, b, c, d, fpa, fpb );


     INPUTS:
          n		number of interpolating points
          x		array containing interpolating points
          f		array containing function values to
			be interpolated;  f[i] is the function
			value corresponding to x[i]
          b		array of size at least n; contents will
			be overwritten
          c		array of size at least n; contents will
			be overwritten
          d		array of size at least n; contents will
			be overwritten
          fpa		derivative of function at x=a
          fpb		derivative of function at x=b


     OUTPUTS:
          b		coefficients of linear terms in cubic 
			spline
	  c		coefficients of quadratic terms in
			cubic spline
	  d		coefficients of cubic terms in cubic
			spline

     REMARK:
          remember that the constant terms in the cubic spline
          are given by the function values being interpolated;
          i.e., the contents of the f array are the constant
          terms

          to evaluate the cubic spline, use the routine
          'spline_eval'
*/
                     
{
     double *h,
            *dl,
            *dd,
            *du;
     int i;
     
     h  = new double [n];
     dl = new double [n];
     dd = new double [n];
     du = new double [n];
     
     for ( i = 0; i < n-1; i++ ) {
         h[i] = x[i+1] - x[i];
         dl[i] = du[i] = h[i];
     }
     
     dd[0] = 2.0 * h[0];
     dd[n-1] = 2.0 * h[n-2];
     c[0] = ( 3.0 / h[0] ) * ( f[1] - f[0] ) - 3.0 * fpa;
     c[n-1] = 3.0 * fpb - ( 3.0 / h[n-2] ) * ( f[n-1] - f[n-2] );
     for ( i = 0; i < n-2; i++ ) {
         dd[i+1] = 2.0 * ( h[i] + h[i+1] );
         c[i+1] = ( 3.0 / h[i+1] ) * ( f[i+2] - f[i+1] ) -
                  ( 3.0 / h[i] ) * ( f[i+1] - f[i] );
     }
     
     tridiagonal ( n, dl, dd, du, c );
     
     for ( i = 0; i < n-1; i++ ) {
         d[i] = ( c[i+1] - c[i] ) / ( 3.0 * h[i] );
         b[i] = ( f[i+1] - f[i] ) / h[i] - h[i] * ( c[i+1] + 2.0*c[i] ) / 3.0;
     }
     
     delete [] h;
     delete [] du;
     delete [] dd;
     delete [] dl;
}


double spline_eval ( int n, double *x, double *f, double *b, double *c,
                     double *d, double t )

/*
     PURPOSE:
          evaluate a cubic spline at a single value of 
          the independent variable given the coefficients of
          the cubic spline interpolant (obtained from 
          'cubic_nak' or 'cubic_clamped')


     CALLING SEQUENCE:
          y = spline_eval ( n, x, f, b, c, d, t );
          spline_eval ( n, x, f, b, c, d, t );


     INPUTS:
          n		number of interpolating points
          x		array containing interpolating points
          f		array containing the constant terms from 
			the cubic spline (obtained from 'cubic_nak'
			or 'cubic_clamped')
          b		array containing the coefficients of the
			linear terms from the cubic spline 
			(obtained from 'cubic_nak' or 'cubic_clamped')
          c		array containing the coefficients of the
			quadratic terms from the cubic spline 
			(obtained from 'cubic_nak' or 'cubic_clamped')
          d		array containing the coefficients of the
			cubic terms from the cubic spline 
			(obtained from 'cubic_nak' or 'cubic_clamped')
          t		value of independent variable at which
			the interpolating polynomial is to be
			evaluated


     OUTPUTS:
          y		value of cubic spline at the specified 
			value of the independent variable
*/

{
     int i,
         found;

     i = 1;
     found = 0;
     while ( !found && ( i < n-1 ) ) {
           if ( t < x[i] )
              found = 1;
           else
              i++;
     }
     t = f[i-1] + ( t - x[i-1] ) * ( b[i-1] + ( t - x[i-1] ) * ( c[i-1] +
                  ( t - x[i-1] ) * d[i-1] ) );
     return ( t );
}

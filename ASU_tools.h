
/***********************************************************
 * This file declares C functions of libASU_tools.a
 *
 * Shule Yu
 * Note: Use this file to avoid implicit function define.
***********************************************************/
#ifndef ASU_TOOLS_H
#define ASU_TOOLS_H

double amplitude(float *, int);
double amplituded(double *, int);
double binary_search(double (*)(double), double, double, double, double);
void   bootstrap(double **, int, int, int, double *, double *, double **, int, double *);
int    bottom_depth(double, double, char *, double *);
int    bottom_location(double, double, double, double, double, char *, double *, double *, double *);
int    bottom_location_fp(double, double, double, double, double, char *, double *, double *, double *, double, char *);
void   butterworth_bp(double **, int, int, double, int, int, double, double, double **);
void   butterworth_hp(double **, int, int, double, int, int, double, double **);
void   butterworth_lp(double **, int, int, double, int, int, double, double **);
void   cart2sph(double, double, double, double *, double *, double *);
void   cbin_update(double *, double *, int, double *, double *, double *, int, int **);
int    CC(double *, int, double *, int, int *, double *);
int    CC_limitshift(double *, int, double *, int, int *, double *, double, double);
int    CC_positive(double *, int, double *, int, int *, double *, int);
int    CC_static(double *, int, double *, int, double *);
int    CC_static_energy(double *, int, double *, int, double *);
int    CC_trace(double *, int, double *, int, int *, double *, double *);
void   cmt2tp(double, double, double, double *, double *);
double combination(int, int);
void   complex_divide(double, double, double, double, double *, double *);
void   confidence(double *, int, double *, double);
void   convolve(double *, double *, int, int, double *);
void   crossproduct(double, double, double, double, double, double, double*, double *, double *);
double crossproduct_2d(double, double, double, double);
double d_rho(double);
double d_vp(double);
double d_vs(double);
double d_rho_smoothed(double,int,int,int,int);
double d_vp_smoothed(double,int,int,int,int);
double d_vs_smoothed(double,int,int,int,int);
void   derivative(double *, int, double *);
void   derivative_f(float *, int, double *);
int    ellipcor_kennett(char *, double, double, double, double, double *);
void   envelope_hilbert(double *, int, double *);
int    filenr(const char *);
int    findjunction(double *, double *, int, double *, double *, int, double, double *, double *);
void   findpeak(double *, int, int *, int, int);
void   findrayp(double *, double *, double *, int, int, double *);
void   findrayp_ulvz(double *, double *, double *, int, int, double *, double, double);
void   freq_amp_phase(double **, int, int, double, double *, double **, double **);
void   gaussblur_1d(double **, int, int, double, double, double, double **);
double gaussian(double, double, double);
void   gaussianfun(double *, int, double, double);
double gcpdistance(double, double, double, double);
void   gmttrans_f(float *, int, int, float *, int *);
void   graycode(int, int**);
double interp2_linear(double *, double, double);
double interp3_linear(double *, double, double, double);
void   linear_fitting(double *, double *, int, double *, double *);
void   ll2tp(double, double, double *, double *);
double lon2360(double);
double lon2180(double);
float  maxval_f(float *, int, int *);
int    max_amp(float *, int, int *);
int    max_ampd(double *, int, int *);
int    max_ampf(float *, int, int *);
double max_vald(double *, int, int *);
int    max_val_i(int *, int, int *);
double mean_d(double *p, int npts);
float  mean_f(float *p, int npts);
double mean_i(int *p, int npts);
int    meshsize(double, double, double, int);
double meshthem(double *, int, double, double, double, int);
float  minval_f(float *, int, int *);
double min_vald(double *, int, int *);
int    mixsize(double *, int);
void   mixthem(double *, int, double **);
double mollifier(double, double);
double normalize(float *, int);
double normalized(double *, int);
double normalize_window(double *, int, int, int);
void   phase_shift(double *, int, double, double *);
int    pick_onset(double *, int, double, int, int);
void   points_in_polygon(double *, double *, int, double *, double *, int, int *);
void   prem(double, int, int, double *, double *, double *, double *, double *, double *, double *, double *);
void   prem_smoothed(double, double *, double *, double *, double *, double *, double *, double *, double *, int, int, int, int);
void   print_2d_array_f(float *, int, int);
double p_norm(double *, int, double);
double p_norm_err(double *, double *, int, double);
double rad_pat(double, double, double, double, double, int);
double rad_pat_loc(double, double, double, double, double, double, double, double, char *, int);
double rad_pat_rayp(double, double, double, double, double, double, int);
double ramp_function(double, double, double);
void   random_gaussian(double *, int, double, double);
void   random_int(int, int, int *, int);
void   random_num(double *, int);
double rayp2takeoff(double, double, int);
int    ray_path(double, int, double *, double *, double, double, double, double *, double *, double *, double *, int *);
int    read_sac(double **, int, int, double *, double, double, double, double, int, int, int, int, double, char **, int *);
int    read_sac_fixdel(double **, int, int *, double *, double, double *, double, double, int, int, int, int, double, char **, int *);
void   redirect_d(double *, int, int, double *);
void   redirect_f(float *, int, int, float *);
void   redirect_i(int *, int, int, int *);
void   retrend(double, float *, int, double);
void   retrendd(double, double *, int, double);
void   reverse_array(double *, int);
void   reverse_array_f(float *, int);
double r_rho(double);
double r_vp(double);
double r_vs(double);
double r_rho_smoothed(double,int,int,int,int);
double r_vp_smoothed(double,int,int,int,int);
double r_vs_smoothed(double,int,int,int,int);
void   shift_array(double *, int, int);
void   shift_array_f(float *, int, int);
void   shift_stack(double **, int, int, int, int *, int, double *, double *, double *);
int    SignalCompare(double *, int, int, double *, int, int, double, double, double, double, int *, double *, double *, double *, double *);
double simpsonx(double (*)(double), double, double, double);
double snr_envelope(double *, int, int, int, int, int);
double snr_peak(double *, int, int, int, int, int);
void   sort_quick(float *, int);
void   sort_quickd(double *, int);
void   sort_quick_i(int *, int);
void   sph2cart(double, double, double, double *, double *, double *);
void   sphdist(double, double, double, double, double, double, double *);
double std_d(double *, int);
double std_err(float *, int);
double std_errd(double *, int);
double std_f(float *, int);
double std_i(int *, int);
double std_weight(double *, double *, int);
void   StretchTrace(double *, int, int, double, double, double, double *);
double sum_d(double *, int);
float  sum_f(float *, int);
int    sum_i(int *, int);
void   taper(float *, int, double);
void   taperd(double *, int, double);
void   taperd_section(double *, int, double, double);
void   tk_decon(double **, int, int, double *, int, int, int *, double **, double, double, int, double *, double *, double **, double **, double **, double **);
void   tp2ll(double, double, double *, double *);
double tpangle(double, double, double, double);
void   trifun(double *, int, double);
void   tstar(double, int, double, double *);
void   union_sets(double *, double *, double *, double *, int, int *);
void   waterlevel_decon(double **, int, int, double *, int, int, int *, double **, double, double, int, double *, double *, double **, double **, double **, double **);
void   waterlevel_decon_wl(double **, int, int, double *, int, int, int *, double **, double *, double, int, double *, double *, double **, double **, double **, double **);
void   waypoint(double, double, double, double, double, double *, double *);
void   waypoint_az(double, double, double, double, double *, double *);
int    waypoint_deeppath(char *, double, double, double, double, double, double, double *, double *, double *, double *);
int    waypoint_sectionpath(char *, double, double, double, double, double, double, int, double **);
void   wiginterp_f(float *, float *, int, double *, double *, int, int);
void   wiginterpd(double *, double *, int, double *, double *, int, int);

#endif

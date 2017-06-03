#ifndef _FHT_H_
#define _FHT_H_

#ifdef __cplusplus
extern "C" {
#endif

void fht_float(float *buf, int log_n);
void fht_double(double *buf, int log_n);

#ifdef __cplusplus
}
#endif

#endif

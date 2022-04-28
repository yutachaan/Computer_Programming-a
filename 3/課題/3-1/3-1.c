#include <stdio.h>
#include <stdlib.h>


// データの特徴次元毎の平均からなる平均ベクトルを計算
double *get_mean(int ndim, double **data, int ndata) {
  // 領域確保
  double *ret;
  if ((ret = (double*)malloc(ndim * sizeof(double))) == NULL) exit(1);

  // 特徴次元ごとに平均を求める
  for (int j = 0; j < ndim; j++) {
    for (int i = 0; i < ndata; i++) ret[j] += data[i][j];
    ret[j] /= ndata;
  }

  return ret;
}


int main(int argc, char *argv[]) {
  FILE *file;
  if ((file = fopen(argv[1], "r")) == NULL) exit(1);

  // フレーム数と特徴次元数を入力
  int ndata, ndim;
  fscanf(file, "%d %d\n", &ndata, &ndim);

  // データの領域確保
  double **data;
  if ((data = (double**)malloc(ndata * sizeof(double*))) == NULL) exit(1);
  for (int i = 0; i < ndata; i++) {
    if ((data[i] = (double*)malloc(ndim * sizeof(double))) == NULL) exit(1);
  }

  // データを入力
  for (int i = 0; i < ndata; i++) {
    for (int j = 0; j < ndim - 1; j++) fscanf(file, "%lf ", &data[i][j]);
    fscanf(file, "%lf\n", &data[i][ndim - 1]);
  }

  fclose(file);


  // 平均ベクトルを求める
  double *mean;
  if ((mean = (double*)malloc(ndim * sizeof(double))) == NULL) exit(1);

  mean = get_mean(ndim, data, ndata);

  for (int j = 0; j < ndim; j++) printf("%lf\n", mean[j]);


  // メモリ解放
  for (int i = 0; i < ndata; i++) free(data[i]);
  free(data);
}

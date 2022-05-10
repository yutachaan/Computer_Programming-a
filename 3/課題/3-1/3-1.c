#include <stdio.h>
#include <stdlib.h>


// データの特徴次元毎の平均からなる平均ベクトルを計算
double *get_mean(int ndim, double **data, int ndata) {
  // 領域確保
  double *mean;
  if ((mean = (double*)malloc(ndim * sizeof(double))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }

  // 特徴次元ごとに平均を求める
  for (int j = 0; j < ndim; j++) {
    for (int i = 0; i < ndata; i++) mean[j] += data[i][j];
    mean[j] /= ndata;
  }

  return mean;
}

// 特徴次元間の分散共分散行列を計算
double **get_cova(int ndim, double **data, int ndata) {
  // 領域確保
  double *mean;
  if ((mean = (double*)malloc(ndim * sizeof(double))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }

  double **cova;
  if ((cova = (double**)malloc(ndim * sizeof(double*))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < ndim; i++) {
    if ((cova[i] = (double*)malloc(ndim * sizeof(double))) == NULL) {
      printf("Memory Allocation Error\n");
      exit(EXIT_FAILURE);
    }
  }

  // 平均を求める
  mean = get_mean(ndim, data, ndata);

  // 分散共分散行列を求める
  for (int i = 0; i < ndim; i++) {
    for (int j = 0; j < ndim; j++) {
      for (int k = 0; k < ndata; k++) {
        cova[i][j] += (data[k][i] - mean[i]) * (data[k][j] - mean[j]);
      }
      cova[i][j] /= ndata;
    }
  }

  return cova;
}


int main(int argc, char *argv[]) {
  FILE *file;
  if ((file = fopen(argv[1], "r")) == NULL) {
    printf("File Open Error: %s\n", file);
    exit(EXIT_FAILURE);
  }

  // フレーム数と特徴次元数を入力
  int ndata, ndim;
  fscanf(file, "%d %d\n", &ndata, &ndim);


  // 領域確保
  double **data;
  if ((data = (double**)malloc(ndata * sizeof(double*))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < ndata; i++) {
    if ((data[i] = (double*)malloc(ndim * sizeof(double))) == NULL) {
      printf("Memory Allocation Error\n");
      exit(EXIT_FAILURE);
    }
  }


  // データを入力
  for (int i = 0; i < ndata; i++) for (int j = 0; j < ndim; j++) {
    fscanf(file, "%lf", &data[i][j]);
  }

  fclose(file);


  // 平均ベクトルを求める
  double *mean;
  if ((mean = (double*)malloc(ndim * sizeof(double))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }

  mean = get_mean(ndim, data, ndata);

  printf("mean vector:\n");
  for (int j = 0; j < ndim; j++) printf("%10lf\n", mean[j]);
  printf("\n");

  free(mean);


  // 分散共分散行列を求める
  double **cova;
  if ((cova = (double**)malloc(ndim * sizeof(double*))) == NULL) {
    printf("Memory Allocation Error\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < ndim; i++) {
    if ((cova[i] = (double*)malloc(ndim * sizeof(double))) == NULL) {
      printf("Memory Allocation Error\n");
      exit(EXIT_FAILURE);
    }
  }

  cova = get_cova(ndim, data, ndata);

  printf("covariance matrix:\n");
  for (int i = 0; i < ndim; i++) {
    for (int j = 0; j < ndim - 1; j++) printf("%10lf ", cova[i][j]);
    printf("%10lf\n", cova[i][ndim - 1]);
  }

  for (int i = 0; i < ndim; i++) free(cova[i]);
  free(cova);


  for (int i = 0; i < ndata; i++) free(data[i]);
  free(data);
}

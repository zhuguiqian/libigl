#include "writeDMAT.h"

#include <cstdio>
#ifndef IGL_NO_EIGEN
#  include <Eigen/Core>
#endif

template <class Mat>
IGL_INLINE bool igl::writeDMAT(
  const std::string file_name, 
  const Mat & W,
  const bool ascii)
{
  FILE * fp = fopen(file_name.c_str(),"w");
  if(fp == NULL)
  {
    fprintf(stderr,"IOError: writeDMAT() could not open %s...",file_name.c_str());
    return false; 
  }
  if(ascii)
  {
    // first line contains number of rows and number of columns
    fprintf(fp,"%d %d\n",(int)W.cols(),(int)W.rows());
    // Loop over columns slowly
    for(int j = 0;j < W.cols();j++)
    {
      // loop over rows (down columns) quickly
      for(int i = 0;i < W.rows();i++)
      {
        fprintf(fp,"%0.17lg\n",(double)W(i,j));
      }
    }
  }else
  {
    // write header for ascii
    fprintf(fp,"0 0\n");
    // first line contains number of rows and number of columns
    fprintf(fp,"%d %d\n",(int)W.cols(),(int)W.rows());
    Eigen::MatrixXd Wd = W.template cast<double>();
    //// Loop over columns slowly
    //for(int j = 0;j < W.cols();j++)
    //{
    //  // loop over rows (down columns) quickly
    //  for(int i = 0;i < W.rows();i++)
    //  {
    //    double d = (double)W(i,j);
    //    fwrite(&d,sizeof(double),1,fp);
    //  }
    //}
    fwrite(Wd.data(),sizeof(double),Wd.size(),fp);
  }
  fclose(fp);
  return true;
}

template <typename Scalar>
IGL_INLINE bool igl::writeDMAT(
  const std::string file_name, 
  const std::vector<std::vector<Scalar> > W)
{
  FILE * fp = fopen(file_name.c_str(),"w");
  if(fp == NULL)
  {
    fprintf(stderr,"IOError: writeDMAT() could not open %s...",file_name.c_str());
    return false; 
  }
  int num_rows = (int)W.size();
  int num_cols = 0;
  if(num_rows > 0)
  {
    num_cols = W[0].size();
  }
  // first line contains number of columns and number of rows
  fprintf(fp,"%d %d\n",num_cols,num_rows);
  // Loop over columns slowly
  for(int j = 0;j < num_cols;j++)
  {
    // loop over rows (down columns) quickly
    for(int i = 0;i < num_rows;i++)
    {
      // better be rectangular
      assert((int)W[i].size() > j);
      fprintf(fp,"%0.15lf\n",(double)W[i][j]);
    }
  }
  fclose(fp);
  return true;
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
// generated by autoexplicit.sh
template bool igl::writeDMAT<Eigen::Matrix<double, -1, -1, 0, -1, -1> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::Matrix<double, -1, -1, 0, -1, -1> const&,bool);
template bool igl::writeDMAT<double>(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::vector<std::vector<double, std::allocator<double> >, std::allocator<std::vector<double, std::allocator<double> > > >);
template bool igl::writeDMAT<Eigen::Matrix<int, -1, -1, 0, -1, -1> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::Matrix<int, -1, -1, 0, -1, -1> const&, bool);
template bool igl::writeDMAT<Eigen::Matrix<double, -1, 1, 0, -1, 1> >(std::basic_string<char, std::char_traits<char>, std::allocator<char> >, Eigen::Matrix<double, -1, 1, 0, -1, 1> const&, bool);
#endif

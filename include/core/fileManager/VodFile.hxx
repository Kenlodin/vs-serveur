/*
 * VodFile.hxx
 *
 *  Created on: 9 mai 2012
 *      Author: nagriar
 */

#ifndef VODFILE_HXX_
#define VODFILE_HXX_

// Internal include
# include <core/fileManager/VodFile.hh>

inline
std::string VodFile::getName() const
{
  return name_;
}

inline
avifile::s_chunk* const * VodFile::getFileHeader() const
{
  return fileHeader_;
}

inline
int VodFile::getIsValid() const
{
  return isValid_;
}

#endif /* VODFILE_HXX_ */

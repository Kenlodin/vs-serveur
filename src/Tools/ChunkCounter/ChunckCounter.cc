/* 
 * File:   ChunckCounter.cc
 * Author: aymeric
 * 
 * Created on 16 mai 2012, 00:34
 */

#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "ChunckCounter.hh"
namespace tools
{

  ChunckCounter::ChunckCounter ()
  {
  }

  ChunckCounter::~ChunckCounter ()
  {
  }

  struct ChunckCounter::result
  ChunckCounter::avi (std::string file)
  {
    avifile::s_chunk chunk_cont;
    avifile::s_sub_chunk chunk;
    avifile::s_hdrl hdrl;
    int count, chunk_nbr = 0, fd, size = 0;
    struct result r;

    if ((fd = open (file.c_str (), O_RDONLY)) == -1)
    {
      COUTDEBUG ("[ChunckCounter] Impossible d'ouvrir le fichier");
      r.length = 0;
      r.size = 0;
      r.nb_packet = 0;
      return r;
    }
    read (fd, &chunk_cont, sizeof (avifile::s_chunk) - sizeof (void*) );
    size = chunk_cont.size;

    read (fd, &chunk_cont, sizeof (avifile::s_chunk) - sizeof (void*) );
    read (fd, &hdrl, sizeof (avifile::s_hdrl));
    lseek (fd, chunk_cont.size - sizeof (void*) - sizeof (avifile::s_hdrl), SEEK_CUR);

    read (fd, &chunk_cont, sizeof (avifile::s_chunk) - sizeof (void*) );
    lseek (fd, chunk_cont.size - sizeof (void*) , SEEK_CUR);
    read (fd, &chunk_cont, sizeof (avifile::s_chunk) - sizeof (void*) );
    lseek (fd, chunk_cont.size - sizeof (void*) , SEEK_CUR);
    read (fd, &chunk_cont, sizeof (chunk_cont) - sizeof (void*) );

    for (count = 0; count < size; )
    {
      read (fd, &chunk, sizeof (chunk));
      chunk.size += chunk.size % 2;
      lseek (fd, chunk.size, SEEK_CUR);
      count += chunk.size + 2 * sizeof (uint32_t);
      chunk_nbr++;
    }
    r.length = (hdrl.MicroSecPerFrame * hdrl.TotalFrame) / 60000000;
    r.size = size;
    r.nb_packet = chunk_nbr;
    close (fd);
    return r;
  }
}
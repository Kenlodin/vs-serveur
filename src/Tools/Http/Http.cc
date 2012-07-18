/* 
 * File:   Http.cc
 * Author: aymeric
 * 
 * Created on 14 mai 2012, 21:29
 */

#include <fcntl.h>
#include <string>

#include <core/tools/http/Http.hh>
namespace tools
{

  Http::Http ()
  {
  }

  Http::~Http ()
  {
  }

  size_t
  Http::writeFile (void* ptr, size_t size, size_t nmemb, FILE* stream)
  {
    return fwrite (ptr, size, nmemb, stream);
  }

  int
  Http::download (std::string url, std::string file)
  {
    CURL* curl = curl_easy_init ();
    FILE* fp;
    if (curl)
    {
      fp = fopen (file.c_str (), "wb");
      if (fp != NULL)
      {
        curl_easy_setopt (curl, CURLOPT_URL, url.c_str ());
        curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, Http::writeFile);
        curl_easy_setopt (curl, CURLOPT_WRITEDATA, fp);
        curl_easy_perform (curl);
        curl_easy_cleanup (curl);
        fclose (fp);
        return 0;
      }
      else
      {
        COUTDEBUG("\t Impossible d'ouvrir le fichier pour écrire");
      }
    }
    return -1;
  }
}

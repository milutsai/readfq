#include <iostream>
#ifdef DYNAMIC_ZLIB
  #include <zlib.h>
#else
  #include "zlib/zlib.h"
#endif

#include "kseq++.h"
#include <string>
using namespace klibpp;

int main()
{
  KSeq record;
  gzFile fp = gzopen("/home/fastq/fastq.gz", "r");
  auto ks = make_kstream(fp, gzread, mode::in);
  //auto ks = KStream(fp, gzread, mode::in);  // C++17
  //auto ks = KStreamIn(fp, gzread);  // C++17
  while (ks >> record) {
    int read_no = 0;
 
    std::cout << "name:" <<record.name << std::endl;
    if (!record.comment.empty()) std::cout << "comment:" << record.comment << std::endl;
    std::cout << "seq:" << record.seq << std::endl;
    if (!record.qual.empty()) std::cout << "qual:" << record.qual << std::endl;
    std::string qual_read;
    qual_read = record.qual;
    
    std::cout << "length of read:" << qual_read.size() << std::endl;
    for(int i=0; i< qual_read.size(); i++){
        int qual = (int)qual_read[i] - 33;
        std::cout << qual;
        
    }
  }
  gzclose(fp);
  return 0;
}

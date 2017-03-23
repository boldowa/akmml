#ifndef D_token2binBuildTime_H
#define D_token2binBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  token2binBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class token2binBuildTime
  {
  public:
    explicit token2binBuildTime();
    virtual ~token2binBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    token2binBuildTime(const token2binBuildTime&);
    token2binBuildTime& operator=(const token2binBuildTime&);

  };

#endif  // D_token2binBuildTime_H

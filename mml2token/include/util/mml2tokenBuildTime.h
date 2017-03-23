#ifndef D_mml2tokenBuildTime_H
#define D_mml2tokenBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  mml2tokenBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class mml2tokenBuildTime
  {
  public:
    explicit mml2tokenBuildTime();
    virtual ~mml2tokenBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    mml2tokenBuildTime(const mml2tokenBuildTime&);
    mml2tokenBuildTime& operator=(const mml2tokenBuildTime&);

  };

#endif  // D_mml2tokenBuildTime_H

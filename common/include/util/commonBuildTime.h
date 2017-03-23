#ifndef D_commonBuildTime_H
#define D_commonBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  commonBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class commonBuildTime
  {
  public:
    explicit commonBuildTime();
    virtual ~commonBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    commonBuildTime(const commonBuildTime&);
    commonBuildTime& operator=(const commonBuildTime&);

  };

#endif  // D_commonBuildTime_H

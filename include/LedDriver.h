#ifndef D_LedDriver_H
#define D_LedDriver_H

///////////////////////////////////////////////////////////////////////////////
//
//  LedDriver is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class LedDriver
  {
  public:
    explicit LedDriver();
    virtual ~LedDriver();

  private:

    LedDriver(const LedDriver&);
    LedDriver& operator=(const LedDriver&);

  };

#endif  // D_LedDriver_H

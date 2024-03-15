#pragma once

class pipe_t
{
  public:
    pipe_t();
    ~pipe_t();

    void *read_end();
    void *write_end();
    void  close_read();
    void  close_write();

  private:
    void *_wstream{ (void *)-1 };
    void *_rstream{ (void *)-1 };
};

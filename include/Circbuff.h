#ifndef D_Circbuff_H
#define D_Circbuff_H

///////////////////////////////////////////////////////////////////////////////
//
//  Circbuff is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

template <int SIZE, typename T>
class Circbuff
  {
  private:
    T elements[SIZE];
    int write_pos;
    int read_pos;
    int num_elements;

  public:
    explicit Circbuff() : write_pos(0), read_pos(0), num_elements(0) {
    }
    virtual ~Circbuff() {
    }

    bool is_empty() {
        return (num_elements==0);
    }

    bool is_full() {
        return (num_elements==SIZE);
    }

    T read() {
        if (is_empty())
            return 0; //Todo: throw empty_buffer_was_read exception
        num_elements--;
        return elements[read_pos++];
    }

    T write(T val) {
        T lost_value=0;

        if (is_full())
            lost_value = read(); //Todo: throw full_buffer_was_written exception
        num_elements++;
        elements[write_pos++] = val;
        return lost_value;
    }

  private:

    Circbuff(const Circbuff&);
    Circbuff& operator=(const Circbuff&);

  };

#endif  // D_Circbuff_H

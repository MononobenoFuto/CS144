#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : 
  capacity_( capacity ), error_(false), end_input(false), total_push(0), total_pop(0), buffer(), op_pointer(0), peek_("") {}

bool Writer::is_closed() const
{
  // Your code here.
  return end_input;
}

void Writer::push( string data )
{
  // Your code here.
  if(end_input) return;

  if(data.length() > available_capacity()) {
    data.resize(available_capacity());
  }
  if(!data.empty()) {
    total_push += data.length();
    buffer.push(move(data));

    if(peek_.empty()) peek_ = buffer.front();
  }

  return;
}

void Writer::close()
{
  // Your code here.
  end_input = true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_ - (total_push - total_pop);
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return total_push;
}

bool Reader::is_finished() const
{
  // Your code here.
  return end_input && (total_pop == total_push);
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return total_pop;
}

string_view Reader::peek() const
{
  // Your code here.
  return peek_;
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  total_pop += len;
  if(len == buffer.front().size()-op_pointer) {
    buffer.pop();
    op_pointer = 0;
    if(bytes_buffered() > 0) peek_ = buffer.front(); else peek_ = "";
  } else {
    op_pointer += len;
    peek_.remove_prefix(len);
  }
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return total_push - total_pop;
}

#include <darc/darc.h>

int main(int argc, const char* argv[])
{
  // Create Node
  darc::NodePtr node = darc::Node::create();

  // Set up node connections manually
  node->accept("udp://127.0.0.1:5120-5130");
  node->connect("udp://127.0.0.1:5120-5130");

  // Instantiate Components
  darc::ComponentPtr c1 = node->instantiateComponent("OpenCVImgFileComponent");

  assert(c1.get());

  // Run Components (These are non-blocking)
  c1->run();

  // Run Node in main thread
  node->runCurrentThread(); // This is blocking
  return 0;
}

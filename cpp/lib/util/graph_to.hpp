template <typename E>
int graph_to(const E& e) {
  return e.to;
}
int graph_to(int e) { return e; }

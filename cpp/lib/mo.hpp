#include "base.hpp"

class Mo {
 public:
  vector<pair<int, int>> queries;

 public:
  int add_query(int l, int r) {
    queries.push_back({l, r});
    return queries.size() - 1;
  }

  template <typename AddL, typename SubL, typename AddR, typename SubR,
            typename Answer, typename T = decltype(declval<Answer>()(0, 0))>
  vector<T> make_answers(const AddL& add_l, const SubL& sub_l,
                         const AddR& add_r, const SubR& sub_r,
                         const Answer& answer) {
    int qn = queries.size();
    int n = 0;
    rep(i, qn) { n = max(queries[i].second, n); }
    int sq_qn = 1;
    while (sq_qn * sq_qn < qn) {
      ++sq_qn;
    }
    int b = max(n / sq_qn, 1);
    vector<tuple<int, int, int>> sq(qn);
    rep(i, qn) {
      int l = queries[i].first;
      int r = queries[i].second;
      int group = l / b;
      sq[i] = make_tuple(group, group % 2 == 0 ? r : -r, i);
    }
    sort(sq.begin(), sq.end());
    vector<T> answers(qn);
    int cl = 0;
    int cr = 0;
    for (auto& t : sq) {
      int i = get<2>(t);
      int l = queries[i].first;
      int r = queries[i].second;
      while (cr < r) {
        add_r(cr++);
      }
      while (cr > r) {
        sub_r(cr--);
      }
      while (cl < l) {
        add_l(cl++);
      }
      while (cl > l) {
        sub_l(cl--);
      }
      answers[i] = answer(cl, cr);
    }
    return answers;
  }

  template <typename Push, typename Pop, typename Answer,
            typename T = decltype(declval<Answer>()(0, 0))>
  vector<T> make_answers(const Push& push, const Pop& pop,
                         const Answer& answer) {
    return make_answers([&](int l) { pop(l); }, [&](int l) { push(l - 1); },
                        [&](int r) { push(r); }, [&](int r) { pop(r - 1); },
                        answer);
  }
};

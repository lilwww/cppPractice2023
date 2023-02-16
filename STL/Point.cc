#include <iostream>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::vector;

class Score
{
	friend struct StuCompare;

private:
	/* data */
	float _math;
	float _Eng;
	float _total;

public:
	Score(float m, float e) : _math(m), _Eng(e), _total(m + e) {}
	~Score() {}
};

struct StuCompare
{
	// ascend
	bool operator()(const Score &t1, const Score &t2) const
	{
		return t1._total < t2._total || (t1._total == t2._total) && (t1._math > t2._math) || (t1._math == t2._math) && (t1._Eng > t2._Eng);
	}
};

void test()
{
    vector<Score> vec{Score(91, 82), Score(81, 92), Score(88, 93)};
    if (vec)
}
int main(int argc, char **argv)
{
    return 0;
}

#include "unilib/unilib/unicode.h"
using namespace ufal::unilib;
typedef unicode u;

#include <iomanip>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

map<u::category_t, vector<u::category_t>> aggregate_categories {
	{ u::LC, { u::Lu, u::Ll, u::Lt } },
	{ u::L, { u::Lu, u::Ll, u::Lt, u::Lm, u::Lo } },
	{ u::M, { u::Mn, u::Mc, u::Me } },
	{ u::N, { u::Nd, u::Nl, u::No } },
	{ u::P, { u::Pc, u::Pd, u::Ps, u::Pe, u::Pi, u::Pf, u::Po } },
	{ u::S, { u::Sm, u::Sc, u::Sk, u::So } },
	{ u::Z, { u::Zs, u::Zl, u::Zp } },
	{ u::C, { u::Cc, u::Cf, u::Cs, u::Co, u::Cn } },
};

map<u::category_t, string> const category_names {
	{ u::Lu, "Lu" },
	{ u::Ll, "Ll" },
	{ u::Lt, "Lt" },
	{ u::LC, "LC" },
	{ u::Lm, "Lm" },
	{ u::Lo, "Lo" },
	{ u::L, "L" },
	{ u::Mn, "Mn" },
	{ u::Mc, "Mc" },
	{ u::Me, "Me" },
	{ u::M, "M" },
	{ u::Nd, "Nd" },
	{ u::Nl, "Nl" },
	{ u::No, "No" },
	{ u::N, "N" },
	{ u::Pc, "Pc" },
	{ u::Pd, "Pd" },
	{ u::Ps, "Ps" },
	{ u::Pe, "Pe" },
	{ u::Pi, "Pi" },
	{ u::Pf, "Pf" },
	{ u::Po, "Po" },
	{ u::P, "P" },
	{ u::Sm, "Sm" },
	{ u::Sc, "Sc" },
	{ u::Sk, "Sk" },
	{ u::So, "So" },
	{ u::S, "S" },
	{ u::Zs, "Zs" },
	{ u::Zl, "Zl" },
	{ u::Zp, "Zp" },
	{ u::Z, "Z" },
	{ u::Cc, "Cc" },
	{ u::Cf, "Cf" },
	{ u::Cs, "Cs" },
	{ u::Co, "Co" },
	{ u::Cn, "Cn" },
	{ u::C, "C" },
};

int main() {
	// build the map of categories and their code point ranges
	map<u::category_t, vector<pair<int, int>>> category_ranges;
	for (char32_t cp = 0; cp != 0x10'FFFF + 1; ++cp) {
		auto const category = u::category(cp);
		auto & ranges = category_ranges[category];

		if (ranges.empty() || ranges.back().second + 1 != cp)
			ranges.emplace_back(cp, cp);
		else
			ranges.back().second = cp;
	}

	// write the categories and their ranges as re2c definitions
	cout << "/*!re2c" << endl;
	for (auto const & category_name : category_names) {
		cout << category_name.second << " = ";
		if (!aggregate_categories.contains(category_name.first)) {
			cout << "[";
			for (auto const & range : category_ranges[category_name.first]) {
				cout << "\\U" << setfill('0') << setw(8) << right << hex << range.first;
				if (range.first != range.second)
					cout << "-\\U" << setfill('0') << setw(8) << right << hex << range.second;
			}
			cout << "];" << endl;
		}
		else {
			auto const & categories = aggregate_categories[category_name.first];
			for (auto it = categories.cbegin(); it != categories.cend() - 1; ++it) {
				cout << category_names.at(*it) << " | ";
			}
			cout << category_names.at(categories.back()) << ";" << endl;
		}
	}
	cout << "*/" << endl;
}
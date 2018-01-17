#pragma once

#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <exception>
#include <iostream>

using namespace std;

namespace Utils {

	template<class T>
	ostream& operator <<(ostream& os, const set<T>& s) {
		os << "{";
		bool first = true;
		for ( const auto& x : s ) {
			if ( !first ) {
				os << ", ";
			}
			first = false;
			os << x;
		}
		return os << "}";
	}

	template<class T>
	ostream& operator <<(ostream& os, const vector<T>& s) {
		os << "[";
		bool first = true;
		for ( const auto& x : s ) {
			if ( !first ) {
				os << ", ";
			}
			first = false;
			os << x;
		}
		return os << "]";
	}

	template<class K, class V>
	ostream& operator <<(ostream& os, const map<K, V>& m) {
		os << "{";
		bool first = true;
		for ( const auto& kv : m ) {
			if ( !first ) {
				os << ", ";
			}
			first = false;
			os << kv.first << ": " << kv.second;
		}
		return os << "}";
	}

	template<class T, class U>
	void AssertEqual(const T& t, const U& u, const string& hint = "") {
		if ( t != u ) {
			ostringstream os;
			os << "Assertion failed: " << t << " != " << u;
			if ( !hint.empty() ) {
				os << " hint: " << hint;
			}
			throw runtime_error(os.str());
		}
	}

	void Assert(bool b, const string& hint = "") {
		AssertEqual(b, true, hint);
	}

	class TestRunner {
	public:
		TestRunner(const string& prefix = "") :
				_prefix(prefix) {
		}

		template<class TestFunc>
		void RunTest(TestFunc func, const string& testName) {
			try {
				func();
				if ( !_prefix.empty() ) {
					cerr << _prefix << ".";
				}
				cerr << testName << " OK" << endl;
			} catch ( runtime_error& e ) {
				++_failCount;
				cerr << testName << " fail: " << e.what() << endl;
			}
		}

		~TestRunner() {
			if ( _failCount > 0 ) {
				cerr << _failCount << " unit tests failed. Terminate" << endl;
				exit(1);
			}
		}

	private:
		const string _prefix;
		int _failCount = 0;
	};

}

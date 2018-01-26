#pragma once

#include <iostream>

#include "../Component.h"

namespace ECS {
	struct Position: Component {
		int X;
		int Y;

		Position(int x, int y) {
			Name = "Position";
			X = x;
			Y = y;
		}
	};

	ostream& operator <<(ostream& s, const Position& p) {
		if ( s ) {
			s << "{" << p.X << ", " << p.Y << "}";
		}
		return s;
	}

	bool operator ==(const Position& lhr, const Position& rhr) {
		return (lhr.X == rhr.X) && (lhr.Y == rhr.Y);
	}

	bool operator !=(const Position& lhr, const Position& rhr) {
		return !(lhr == rhr);
	}

	bool operator >(const Position& a, const Position& b) {
		if ( a.Y > b.Y ) {
			return true;
		} else if ( a.Y == b.Y ) {
			return a.X > b.X;
		}
		return false;
	}

	bool operator <(const Position& a, const Position& b) {
		if ( a.Y < b.Y ) {
			return true;
		} else if ( a.Y == b.Y ) {
			return a.X < b.X;
		}
		return false;
	}
}


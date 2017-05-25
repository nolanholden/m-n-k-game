#ifndef IPRINTABLE_H
#define IPRINTABLE_H

namespace tttsolver {
namespace implementation {
namespace interfaces {

	class IPrintable {
	public:
		// Print something to the screen.
		virtual void Print() const = 0;
		virtual ~IPrintable() {}
	};
} // namespace interfaces
} // namespace implementation
} // namespace tttsolver

#endif // IPRINTABLE_H

#ifndef CSE_VALUE_H
#define CSE_VALUE_H
namespace cse {
	class Value {
		// The least-significant bit of the first word of Value *must* be zero:
		//   http://www.llvm.org/docs/ProgrammersManual.html#the-waymarking-algorithm
		//Type* VTy;
		//Use* UseList;
	protected:
		//Value(Type* Ty, unsigned scid);

		/// Value's destructor should be virtual by design, but that would require
		/// that Value and all of its subclasses have a vtable that effectively
		/// duplicates the information in the value ID. As a size optimization, the
		/// destructor has been protected, and the caller should manually call
		/// deleteValue.
		~Value(); // Use deleteValue() to delete a generic Value.

	public:
		Value();
		//Value(const Value&) = delete;
		//Value& operator=(const Value&) = delete;
	};
}
#endif // CSE_VALUE_H
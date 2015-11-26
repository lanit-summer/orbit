package orbit.model;

public class vector_of_return_values {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected vector_of_return_values(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(vector_of_return_values obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        orbitJNI.delete_vector_of_return_values(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public vector_of_return_values() {
    this(orbitJNI.new_vector_of_return_values__SWIG_0(), true);
  }

  public vector_of_return_values(long n) {
    this(orbitJNI.new_vector_of_return_values__SWIG_1(n), true);
  }

  public long size() {
    return orbitJNI.vector_of_return_values_size(swigCPtr, this);
  }

  public long capacity() {
    return orbitJNI.vector_of_return_values_capacity(swigCPtr, this);
  }

  public void reserve(long n) {
    orbitJNI.vector_of_return_values_reserve(swigCPtr, this, n);
  }

  public boolean isEmpty() {
    return orbitJNI.vector_of_return_values_isEmpty(swigCPtr, this);
  }

  public void clear() {
    orbitJNI.vector_of_return_values_clear(swigCPtr, this);
  }

  public void add(ReturnValues x) {
    orbitJNI.vector_of_return_values_add(swigCPtr, this, ReturnValues.getCPtr(x), x);
  }

  public ReturnValues get(int i) {
    return new ReturnValues(orbitJNI.vector_of_return_values_get(swigCPtr, this, i), false);
  }

  public void set(int i, ReturnValues val) {
    orbitJNI.vector_of_return_values_set(swigCPtr, this, i, ReturnValues.getCPtr(val), val);
  }

}

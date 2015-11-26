package orbit.model;


public class orbit {
  public static vector_of_return_values computeFlightPlan(ShipPosition initialPosition, ShipParams shipParams, Quants quants) {
    return new vector_of_return_values(orbitJNI.computeFlightPlan(ShipPosition.getCPtr(initialPosition), initialPosition, ShipParams.getCPtr(shipParams), shipParams, Quants.getCPtr(quants), quants), true);
  }

}

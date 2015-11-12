package orbit.view;

import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.scene.control.TextArea;
import javafx.scene.control.Alert.AlertType;



import javafx.fxml.FXML;
import orbit.model.Ship;


public class gameController {



	@FXML
	private TextField shipEdgeLength;
	@FXML
	private TextField shipMass;
	@FXML
	private TextField fuelMass;
	@FXML
	private TextField maxFuelUsagePerSec;
	@FXML
	private TextField impulsePerFuel;
	@FXML
	private TextField maxOverload;
	@FXML
	private TextField maxHeating;
	@FXML
	private TextField initialX;
	@FXML
	private TextField initialY;
	@FXML
	private TextField initialZ;
	@FXML
	private TextField orientationX;
	@FXML
	private TextField orientationY;
	@FXML
	private TextField orientationZ;
	@FXML
	private TextField rotationX;
	@FXML
	private TextField rotationY;
	@FXML
	private TextField rotationZ;
	@FXML
	private TextField maxRotationX;
	@FXML
	private TextField maxRotationY;
	@FXML
	private TextField maxRotationZ;
	@FXML
	private TextArea commands;
	@FXML
	private TextField quantsize;
	@FXML
	private TextField quantnumber;


	private Ship ship;

	public void handleGetTrajectory(){
		if (isValid()){
			this.ship = new Ship(Double.parseDouble(this.shipEdgeLength.getText()),
				Double.parseDouble(this.shipMass.getText()),Double.parseDouble(this.fuelMass.getText()),
				Double.parseDouble(this.maxFuelUsagePerSec.getText()),Double.parseDouble(this.impulsePerFuel.getText()),
				Double.parseDouble(this.maxOverload.getText()),Double.parseDouble(this.maxHeating.getText()));

			this.ship.setInitial(Double.parseDouble(this.initialX.getText()),
				Double.parseDouble(this.initialY.getText()),
				Double.parseDouble(this.initialZ.getText()));

			this.ship.setOrientation(Double.parseDouble(this.orientationX.getText()),
				Double.parseDouble(this.orientationY.getText()),
				Double.parseDouble(this.orientationZ.getText()));

			this.ship.setMaxRotation(Double.parseDouble(this.maxRotationX.getText()),
				Double.parseDouble(this.maxRotationY.getText()),
				Double.parseDouble(this.maxRotationZ.getText()));

			this.ship.setQuants(Integer.parseInt(this.quantsize.getText()), Integer.parseInt(this.quantnumber.getText()));

			if(commands.getText() != null || commands.getText().length() != 0){
				String cmd =  commands.getText().replace('\n', ',').replace(' ', '=');
				System.out.println(cmd);
				this.ship.setCommands(cmd);
			}

			this.ship.makeTrajectory();

			Alert alert = new Alert(AlertType.INFORMATION);
	        alert.setTitle("Траетория готова");
	        alert.setHeaderText("Расположена в файле trajectory.xyzv");
	        alert.showAndWait();

		}

	}


	public void setTest(){
		initialX.setText("0");
		initialY.setText("0");
		initialZ.setText("6578.1");

		orientationX.setText("0");
		orientationY.setText("0");
		orientationZ.setText("1");

		shipEdgeLength.setText("0.001");
		shipMass.setText("3.0");
		fuelMass.setText("10.0");
		maxFuelUsagePerSec.setText("100.0");
		impulsePerFuel.setText("20.0");
		maxOverload.setText("2.0");
		maxHeating.setText("100.0");

		maxRotationX.setText("10.0");
		maxRotationY.setText("10.0");
		maxRotationZ.setText("10.0");

		quantsize.setText("10");
		quantnumber.setText("10");


	}

	private boolean isValid(){
		String errorMessage ="";
		if (shipEdgeLength.getText() == null || shipEdgeLength.getText().length() == 0) {
	           errorMessage += "Не указана длина!\n";
		}
		if (shipMass.getText() == null || shipMass.getText().length() == 0) {
	           errorMessage += "Не указана масса!\n";
		}
		if (fuelMass.getText() == null || fuelMass.getText().length() == 0) {
	           errorMessage += "Не указана масса топлива!\n";
		}
		if (maxFuelUsagePerSec.getText() == null || maxFuelUsagePerSec.getText().length() == 0) {
	           errorMessage += "Не указан максимальный расход топлива!\n";
		}
		if (impulsePerFuel.getText() == null || impulsePerFuel.getText().length() == 0) {
	           errorMessage += "Не указан удельный импульс двигателя!\n";
		}
		if (maxOverload.getText() == null || maxOverload.getText().length() == 0) {
	           errorMessage += "Не указана предельная нагрузка!\n";
		}
		if (maxHeating.getText() == null || maxHeating.getText().length() == 0) {
	           errorMessage += "Не указан максимальный нагрев!\n";
		}
		if (orientationX.getText() == null || orientationX.getText().length() == 0 ||
			orientationY.getText() == null || orientationY.getText().length() == 0 ||
			orientationZ.getText() == null || orientationZ.getText().length() == 0) {
		       errorMessage += "Не указана ориентация в пространстве!\n";
		}
		if (initialX.getText() == null || initialX.getText().length() == 0 ||
			initialY.getText() == null || initialY.getText().length() == 0 ||
			initialZ.getText() == null || initialZ.getText().length() == 0) {
			   errorMessage += "Не указано положение в пространстве!\n";
		}
		if (maxRotationX.getText() == null || maxRotationX.getText().length() == 0 ||
			maxRotationY.getText() == null || maxRotationY.getText().length() == 0 ||
			maxRotationZ.getText() == null || maxRotationZ.getText().length() == 0) {
				   errorMessage += "Не указан максимальный момент вращения!\n";
		}
		if (quantsize.getText() == null || quantsize.getText().length() == 0 ||
			quantnumber.getText()==null || quantnumber.getText().length() == 0){
				errorMessage += "Не указан квант!\n";
			}
		if (errorMessage.length() == 0) {
            return true;
        } else {
            Alert alert = new Alert(AlertType.ERROR);
            alert.setTitle("Ошибка!");
            alert.setHeaderText("Исправьте следующие поля");
            alert.setContentText(errorMessage);
            alert.showAndWait();
            return false;

        }
	}
}

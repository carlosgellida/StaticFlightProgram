class App extends React.Component{
  constructor(props){
    super(props) ; 
    this.state = {
      motor1: 0, 
      motor2: 0, 
      servo1: 0, 
      servo2: 0, 
      servo3: 0
    }
    this.updateMotor1 = this.updateMotor1.bind(this) ; 
    this.updateMotor2 = this.updateMotor2.bind(this) ;
    this.updateServo1 = this.updateServo1.bind(this) ;
    this.sendData = this.sendData.bind(this); 
  }
  
  updateMotor1(e){
    this.setState({
      motor1: e.target.value,
    })
  }
  
   updateMotor2(e){
    this.setState({
      motor2: e.target.value,
    })
   }
     
    updateServo1(e){
    this.setState({
      servo1: e.target.value,
    }, ()=>{this.sendData()})
    }
  
    sendData(){
      fetch('/senData?servo1='+this.state.servo1)
      //.then(response => response.json())
      //.then(data => {
      //  document.getElementById('message').innerHTML = JSON.stringify(data);
      //})
    }
  
  render(){
    return(
      <div id="mainContainer"> 
          <h1> Remote control of motors and servomotors </h1>
        
        <p className="actuator">Motor 1: </p>
        <div id="bottonZoneMotor1" className="bottonZone">
          <input className="bars" type="range"
          value={this.state.motor1}
          min="0"
          max="255"
          step="1"
          onChange={this.updateMotor1}
          />
          <div className="output">{this.state.motor1}</div>
        </div>
        
        <p className="actuator">Motor 2: </p>
        <div id="bottonZoneMotor2" className="bottonZone" >
          <input className="bars" type="range"
          value={this.state.motor2}
          min="0"
          max="255"
          step="1"
          onChange={this.updateMotor2}
          />
          <div className="output">{this.state.motor2}</div>
        </div>
        
        <p className="actuator">Servo 1: </p>
        <div id="bottonZoneServo1" className="bottonZone" >
          <input className="bars" type="range"
          value={this.state.servo1}
          min="0"
          max="180"
          step="1"
          onChange={this.updateServo1}
          />
          <div className="output">{this.state.servo1}</div>
        </div>
      </div>
    ) ; 
  }
}

ReactDOM.render(<App />, document.getElementById('app')); 
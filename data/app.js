class App extends React.Component{
  constructor(props){
    super(props) ; 
    this.state = {
      motor0: 0, 
      motor1: 0, 
      servo0: 0, 
      servo1: 0, 
      servo2: 0
    }
    this.updateMotor0 = this.updateMotor0.bind(this) ; 
    this.updateMotor1 = this.updateMotor1.bind(this) ;
    this.updateServo0 = this.updateServo0.bind(this) ;
    this.updateServo1 = this.updateServo1.bind(this) ;
    this.updateServo2 = this.updateServo2.bind(this) ;
    this.sendServo0Data = this.sendServo0Data.bind(this); 
    this.sendServo1Data = this.sendServo1Data.bind(this); 
    this.sendServo2Data = this.sendServo2Data.bind(this); 
    this.sendMotor0Data = this.sendMotor0Data.bind(this); 
    this.sendMotor1Data = this.sendMotor1Data.bind(this); 
  }
  
  updateMotor0(e){
    this.setState({
      motor0: e.target.value,
    }, ()=>{this.sendMotor0Data()})
  }
  
   updateMotor1(e){
    this.setState({
      motor1: e.target.value,
    }, ()=>{this.sendMotor1Data()})
   }
     
    updateServo0(e){
    this.setState({
      servo0: e.target.value,
    }, ()=>{this.sendServo0Data()})
    }

    updateServo1(e){
      this.setState({
        servo1: e.target.value,
      }, ()=>{this.sendServo1Data()})
      }

      updateServo2(e){
        this.setState({
          servo2: e.target.value,
        }, ()=>{this.sendServo2Data()})
        }

    sendMotor0Data(){
      fetch('/senData?motor0='+this.state.motor0)
    }

    sendMotor1Data(){
      fetch('/senData?motor1='+this.state.motor1)
    }
  
    sendServo0Data(){
      fetch('/senData?servo0='+this.state.servo0)
    }

    sendServo1Data(){
      fetch('/senData?servo1='+this.state.servo1)
    }

    sendServo2Data(){
      fetch('/senData?servo2='+this.state.servo2)
    }
  
  render(){
    return(
      <div id="mainContainer"> 
          <h1> Remote control of motors and servomotors </h1>
        
        <p className="actuator">Motor 0: </p>
        <div id="bottonZoneMotor0" className="bottonZone">
          <input className="bars" type="range"
          value={this.state.motor0}
          min="0"
          max="200"
          step="1"
          onChange={this.updateMotor0}
          />
          <div className="output">{this.state.motor0}</div>
        </div>
        
        <p className="actuator">Motor 1: </p>
        <div id="bottonZoneMotor1" className="bottonZone" >
          <input className="bars" type="range"
          value={this.state.motor1}
          min="0"
          max="200"
          step="1"
          onChange={this.updateMotor1}
          />
          <div className="output">{this.state.motor1}</div>
        </div>
        
        <p className="actuator">Servo 0: </p>
        <div id="bottonZoneServo0" className="bottonZone" >
          <input className="bars" type="range"
          value={this.state.servo0}
          min="-30"
          max="30"
          step="1"
          onChange={this.updateServo0}
          />
          <div className="output">{this.state.servo0}</div>
        </div>

        <p className="actuator">Servo 1: </p>
        <div id="bottonZoneServo1" className="bottonZone" >
          <input className="bars" type="range"
          value={this.state.servo1}
          min="-30"
          max="30"
          step="1"
          onChange={this.updateServo1}
          />
          <div className="output">{this.state.servo1}</div>
        </div>

        <p className="actuator">Servo 2: </p>
        <div id="bottonZoneServo2" className="bottonZone" >
          <input className="bars" type="range"
          value={this.state.servo2}
          min="-30"
          max="30"
          step="1"
          onChange={this.updateServo2}
          />
          <div className="output">{this.state.servo2}</div>
        </div>
      </div>
    ) ; 
  }
}

ReactDOM.render(<App />, document.getElementById('app')); 
const sounds = {
  Q: 'https://s3.amazonaws.com/freecodecamp/drums/Heater-1.mp3', 
  W: 'https://s3.amazonaws.com/freecodecamp/drums/Heater-2.mp3', 
  E: 'https://s3.amazonaws.com/freecodecamp/drums/Heater-3.mp3',
  A: 'https://s3.amazonaws.com/freecodecamp/drums/Heater-4_1.mp3',
  S: 'https://s3.amazonaws.com/freecodecamp/drums/Heater-6.mp3',
  D: 'https://s3.amazonaws.com/freecodecamp/drums/Dsc_Oh.mp3',
  Z: 'https://s3.amazonaws.com/freecodecamp/drums/Kick_n_Hat.mp3',
  X: 'https://s3.amazonaws.com/freecodecamp/drums/RP4_KICK_1.mp3',
  C: 'https://s3.amazonaws.com/freecodecamp/drums/Cev_H2.mp3'
}

class App extends React.Component {
  constructor(props){
    super(props); 
    this.state = {
      tecla: '',
    }
    this.handleClick = this.handleClick.bind(this); 
  }
  
  handleClick(e, letter, i){
    const currentSound = document.getElementById(letter)
    currentSound.currentTime = 0;
    currentSound.play(); 
    this.setState({
      tecla: letter
    })
    
  }
  onKeyPressed(e){
    const currentSound = document.getElementById(e.key.toUpperCase());
    currentSound.currentTime = 0;
    currentSound.play(); 
    this.setState({
      tecla: e.key.toUpperCase()
    })
  }
  render(){
    
    return(
      <div id="drum-machine" onKeyDown={(e) => this.onKeyPressed(e)}
    tabIndex="0"> 
        <div id="display">
          <p>Welcome to my Drum Machine</p>
          <img src='https://www.stars-music.fr/medias/alesis/strike-pro-hd-3-98918.png' id='battery'/>
          {this.state.tecla}</div>
        <ButtonsKeys handleClick={this.handleClick}/>
      </div>
    );
  }
}

function ButtonsKeys(props){
  const buttonsKeys = ["Q", "W", "E", "A", "S", "D", "Z", "X", "C"]; 
   return( <div className="ButtonsGrid">
       {buttonsKeys.map((letter, i)=>{return(
        <button className="drum-pad" id={"button"+i} onClick={(e) => props.handleClick(e, letter, i)}>{letter}<audio
   src={sounds[letter]} className="clip" id={letter}></audio></button>
         ); } ) 
        } </div> ); 
}

ReactDOM.render(<App />, document.getElementById('app')); 
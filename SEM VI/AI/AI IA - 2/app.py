import streamlit as st
import speech_recognition as sr
import pyttsx3
from gtts import gTTS
import google.generativeai as genai
import os
import re
from googletrans import Translator
from dotenv import load_dotenv

load_dotenv()

# Gemini setup
def setup_gemini():
    api_key = os.getenv("GOOGLE_API_KEY")
    if not api_key:
        st.error("GOOGLE_API_KEY not found. Add it to .env file.")
        return None
    genai.configure(api_key=api_key)
    return genai.GenerativeModel("gemini-1.5-flash")

# Markdown cleaner
def clean_text_for_tts(text):
    text = re.sub(r'\*\*(.*?)\*\*', r'\1', text)
    text = re.sub(r'__(.*?)__', r'\1', text)
    text = re.sub(r'\*(.*?)\*', r'\1', text)
    text = re.sub(r'_(.*?)_', r'\1', text)
    text = re.sub(r'^#{1,6}\s+(.+)$', r'\1', text, flags=re.MULTILINE)
    text = re.sub(r'```.*?\n(.*?)```', r'\1', text, flags=re.DOTALL)
    text = re.sub(r'`(.*?)`', r'\1', text)
    text = re.sub(r'^\s*[-*+]\s+(.+)$', r'\1', text, flags=re.MULTILINE)
    text = re.sub(r'^\s*\d+\.\s+(.+)$', r'\1', text, flags=re.MULTILINE)
    return text.strip()

# TTS setup
def get_tts_engine():
    engine = pyttsx3.init()
    engine.setProperty('rate', 180)
    return engine

# TTS logic
def text_to_speech(text, engine, lang_code):
    cleaned_text = clean_text_for_tts(text)
    try:
        if lang_code == "en":
            temp_file = "temp_audio.mp3"
            engine.save_to_file(cleaned_text, temp_file)
            engine.runAndWait()
            with open(temp_file, "rb") as f:
                audio_bytes = f.read()
            os.remove(temp_file)
            return audio_bytes
        else:
            tts = gTTS(cleaned_text, lang=lang_code)
            tts.save("temp.mp3")
            with open("temp.mp3", "rb") as f:
                audio = f.read()
            os.remove("temp.mp3")
            return audio
    except Exception as e:
        st.error(f"TTS Error: {e}")
        return None

# Translation
def translate(text, dest='en'):
    translator = Translator()
    return translator.translate(text, dest=dest).text

# Voice recognition
def recognize_speech():
    r = sr.Recognizer()
    try:
        with sr.Microphone() as source:
            r.adjust_for_ambient_noise(source, duration=0.5)
            audio = r.listen(source, timeout=5)
            try:
                text = r.recognize_google(audio)
                return text
            except sr.UnknownValueError:
                return "Could not understand audio"
            except sr.RequestError:
                return "Could not request results"
    except Exception as e:
        st.error(f"Error accessing microphone: {e}")
        return "Microphone error"

# Supported languages
LANG_CODES = {
    "English": "en", "Hindi": "hi", "Marathi": "mr", "Gujarati": "gu",
    "French": "fr", "German": "de", "Spanish": "es",
    "Tamil": "ta", "Telugu": "te"
}

def handle_voice_input():
    st.session_state.voice_active = True

def main():
    st.set_page_config(page_title="Gemini Voice Chatbot", page_icon="🤖")

    st.title("🤖 Voice Assistant")

    # Initialize session state variables
    if "messages" not in st.session_state:
        st.session_state.messages = []
    if "tts_engine" not in st.session_state:
        st.session_state.tts_engine = get_tts_engine()
    if "voice_active" not in st.session_state:
        st.session_state.voice_active = False
    if "voice_result" not in st.session_state:
        st.session_state.voice_result = None
    
    # Sidebar setup
    with st.sidebar:
        if os.getenv("GOOGLE_API_KEY"):
            st.success("✅ Yeahhh, lets go!")
        else:
            st.error("❌ Ahh, darn it.")

        st.markdown("### 🌐 Language Selection")
        selected_lang = st.selectbox("Choose a language:", list(LANG_CODES.keys()))
        selected_lang_code = LANG_CODES[selected_lang]

        if st.button("🧹 Clear Chat History"):
            st.session_state.messages = []
            st.rerun()

        st.markdown("#### Team Members")
        st.markdown("""
        - Minav Karia - 083  
        - Yashank Kothari - 089  
        - Romil Lodaya - 096  
        - Aakriti Mehta - 109  
        - Siddhi Somaiya - 255
        """)

        st.markdown("### About")
        st.markdown("Built with ❤️ using Streamlit, Gemini, pyttsx3, gTTS & Google Translate.")
    
    # Display chat history
    for i, msg in enumerate(st.session_state.messages):
        with st.chat_message(msg["role"]):
            st.markdown(msg["content"])
            if msg["role"] == "assistant":
                if st.button("🔊 Listen", key=f"listen_{i}"):
                    audio_data = text_to_speech(msg["content"], st.session_state.tts_engine, selected_lang_code)
                    if audio_data:
                        st.audio(audio_data, format="audio/mp3", autoplay=True)
    
    # Simple voice button
    if st.button("🎤 Voice Input", on_click=handle_voice_input):
        pass
    
    # Handle voice recognition if triggered
    if st.session_state.voice_active:
        with st.spinner("Listening..."):
            spoken_text = recognize_speech()
            
        st.session_state.voice_active = False
        
        if spoken_text and "Could not" not in spoken_text and "Microphone error" not in spoken_text:
            if selected_lang_code != "en":
                translated_text = translate(spoken_text, dest=selected_lang_code)
                st.session_state.voice_result = translated_text
            else:
                st.session_state.voice_result = spoken_text
            st.rerun()
    
    # Process voice result if available
    if st.session_state.voice_result:
        handle_user_query(st.session_state.voice_result, selected_lang_code)
        st.session_state.voice_result = None
    
    # Text input
    prompt = st.chat_input("Type your message here...")
    if prompt:
        handle_user_query(prompt, selected_lang_code)

def handle_user_query(prompt, lang_code):
    st.session_state.messages.append({"role": "user", "content": prompt})
    with st.chat_message("user"):
        st.markdown(prompt)

    with st.chat_message("assistant"):
        with st.spinner("Thinking..."):
            model = setup_gemini()
            if model:
                response = model.generate_content(prompt)
                reply = response.text
                st.markdown(reply)
                st.session_state.messages.append({"role": "assistant", "content": reply})
                audio_data = text_to_speech(reply, st.session_state.tts_engine, lang_code)
                if audio_data:
                    st.audio(audio_data, format="audio/mp3", autoplay=True)

if __name__ == "__main__":
    main()
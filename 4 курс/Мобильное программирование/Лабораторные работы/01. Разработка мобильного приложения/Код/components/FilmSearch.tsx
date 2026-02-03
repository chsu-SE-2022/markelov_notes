'use client';

import React, { useEffect, useMemo, useRef, useState } from 'react';
import { motion, AnimatePresence } from 'framer-motion';
import { Button } from '@/components/ui/button';
import { Search, Loader2, AlertCircle, CornerDownLeft } from 'lucide-react';
import FilmCard from '@/components/FilmCard';
import { KinopoiskFilm } from '@/services/kinopoisk';

interface FilmSearchProps {
  onAddFilm?: (film: KinopoiskFilm) => void;
  className?: string;
}

export default function FilmSearch({ onAddFilm, className = '' }: FilmSearchProps) {
  const [query, setQuery] = useState('');
  const [films, setFilms] = useState<KinopoiskFilm[]>([]);
  const [isLoading, setIsLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [hasSearched, setHasSearched] = useState(false);

  // Typeahead state
  const [suggestions, setSuggestions] = useState<KinopoiskFilm[]>([]);
  const [showSuggestions, setShowSuggestions] = useState(false);
  const [highlightIndex, setHighlightIndex] = useState<number>(-1);
  const suggestionsRef = useRef<HTMLDivElement | null>(null);
  const inputRef = useRef<HTMLInputElement | null>(null);
  const abortRef = useRef<AbortController | null>(null);

  const minChars = 2;
  const maxSuggestions = 8;

  const isAbortError = (e: unknown): e is DOMException => {
    return e instanceof DOMException && e.name === 'AbortError';
  };

  const fetchSuggestions = useMemo(
    () =>
      async (q: string) => {
        if (abortRef.current) {
          abortRef.current.abort();
        }
        abortRef.current = new AbortController();
        try {
          const res = await fetch(`/api/films/search?q=${encodeURIComponent(q)}`, {
            signal: abortRef.current.signal,
          });
          const data = await res.json();
          if (data.success) {
            setSuggestions((data.data.items || []).slice(0, maxSuggestions));
            setShowSuggestions(true);
            setHighlightIndex(-1);
          } else {
            setSuggestions([]);
            setShowSuggestions(false);
          }
        } catch (e) {
          if (!isAbortError(e)) {
            setSuggestions([]);
            setShowSuggestions(false);
          }
        }
      },
    []
  );

  // Debounce user input for typeahead
  useEffect(() => {
    if (query.trim().length < minChars) {
      setSuggestions([]);
      setShowSuggestions(false);
      return;
    }
    const id = setTimeout(() => {
      fetchSuggestions(query.trim());
    }, 300);
    return () => clearTimeout(id);
  }, [query, fetchSuggestions]);

  // Close suggestions on outside click
  useEffect(() => {
    function onClickOutside(e: MouseEvent) {
      if (
        suggestionsRef.current &&
        !suggestionsRef.current.contains(e.target as Node) &&
        inputRef.current &&
        e.target !== inputRef.current
      ) {
        setShowSuggestions(false);
      }
    }
    document.addEventListener('mousedown', onClickOutside);
    return () => document.removeEventListener('mousedown', onClickOutside);
  }, []);

  const handleSearch = async () => {
    if (!query.trim()) return;

    setIsLoading(true);
    setError(null);
    setHasSearched(true);
    setShowSuggestions(false);

    try {
      const response = await fetch(`/api/films/search?q=${encodeURIComponent(query.trim())}`);
      const data = await response.json();

      if (data.success) {
        setFilms(data.data.items || []);
      } else {
        setError(data.error || 'Произошла ошибка при поиске');
        setFilms([]);
      }
    } catch (error) {
      console.error('Ошибка поиска фильмов:', error);
      setError('Произошла ошибка при поиске фильмов');
      setFilms([]);
    } finally {
      setIsLoading(false);
    }
  };

  const selectSuggestion = (idx: number) => {
    if (idx < 0 || idx >= suggestions.length) return;
    const film = suggestions[idx];
    setQuery(film.nameRu || '');
    setShowSuggestions(false);
    // Покажем результаты по выбранному названию
    void handleSearch();
  };

  const onInputKeyDown = (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (!showSuggestions || suggestions.length === 0) {
      if (e.key === 'Enter') {
        e.preventDefault();
        handleSearch();
      }
      return;
    }

    if (e.key === 'ArrowDown') {
      e.preventDefault();
      setHighlightIndex((prev) => (prev + 1) % suggestions.length);
    } else if (e.key === 'ArrowUp') {
      e.preventDefault();
      setHighlightIndex((prev) => (prev - 1 + suggestions.length) % suggestions.length);
    } else if (e.key === 'Enter') {
      e.preventDefault();
      selectSuggestion(highlightIndex === -1 ? 0 : highlightIndex);
    } else if (e.key === 'Escape') {
      setShowSuggestions(false);
    }
  };

  const handleAddFilm = (film: KinopoiskFilm) => {
    if (onAddFilm) {
      onAddFilm(film);
    }
  };

  return (
    <div className={`space-y-6 ${className}`}>
      {/* Поисковая строка */}
      <div className="flex gap-3">
        <div className="flex-1 relative" ref={suggestionsRef}>
          <Search className="absolute left-3 top-1/2 transform -translate-y-1/2 h-5 w-5 text-gray-400" />
          <input
            ref={inputRef}
            type="text"
            value={query}
            onChange={(e) => setQuery(e.target.value)}
            onKeyDown={onInputKeyDown}
            placeholder="Поиск фильмов..."
            className="w-full pl-10 pr-4 py-3 bg-gray-800 border border-gray-700 rounded-xl text-white placeholder-gray-400 focus:outline-none focus:ring-2 focus:ring-pink-500 focus:border-transparent"
          />

          {/* Подсказки */}
          <AnimatePresence>
            {showSuggestions && suggestions.length > 0 && (
              <motion.ul
                initial={{ opacity: 0, y: -4 }}
                animate={{ opacity: 1, y: 0 }}
                exit={{ opacity: 0, y: -4 }}
                className="absolute z-20 mt-2 w-full max-h-80 overflow-auto rounded-xl border border-gray-700 bg-gray-900 shadow-xl"
                role="listbox"
              >
                {suggestions.map((s, idx) => (
                  <li
                    key={s.kinopoiskId}
                    role="option"
                    aria-selected={idx === highlightIndex}
                    onMouseEnter={() => setHighlightIndex(idx)}
                    onMouseDown={(e) => {
                      // предотвратить blur до onClick
                      e.preventDefault();
                    }}
                    onClick={() => selectSuggestion(idx)}
                    className={
                      `flex items-center gap-3 px-3 py-2 cursor-pointer ` +
                      (idx === highlightIndex ? 'bg-gray-800' : 'hover:bg-gray-800')
                    }
                  >
                    <div className="flex-1 min-w-0">
                      <div className="text-sm text-white truncate">{s.nameRu}</div>
                      <div className="text-xs text-gray-400 truncate">
                        {(s.year ? `${s.year} • ` : '') + (s.genres?.map(g => g.genre).join(', ') || '')}
                      </div>
                    </div>
                    <kbd className="hidden sm:flex items-center gap-1 text-[10px] text-gray-400">
                      <CornerDownLeft className="h-3 w-3" /> Enter
                    </kbd>
                  </li>
                ))}
              </motion.ul>
            )}
          </AnimatePresence>
        </div>
        <Button
          onClick={handleSearch}
          disabled={!query.trim() || isLoading}
          className="px-6 py-3 bg-pink-600 hover:bg-pink-700 disabled:bg-gray-600 disabled:cursor-not-allowed rounded-xl"
        >
          {isLoading ? (
            <Loader2 className="h-5 w-5 animate-spin" />
          ) : (
            <Search className="h-5 w-5" />
          )}
        </Button>
      </div>

      {/* Сообщение об ошибке */}
      <AnimatePresence>
        {error && (
          <motion.div
            initial={{ opacity: 0, y: -10 }}
            animate={{ opacity: 1, y: 0 }}
            exit={{ opacity: 0, y: -10 }}
            className="flex items-center gap-2 p-4 bg-red-900 bg-opacity-50 border border-red-700 rounded-xl text-red-200"
          >
            <AlertCircle className="h-5 w-5" />
            <span>{error}</span>
          </motion.div>
        )}
      </AnimatePresence>

      {/* Результаты поиска */}
      <AnimatePresence>
        {hasSearched && !isLoading && (
          <motion.div
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            exit={{ opacity: 0 }}
            className="space-y-4"
          >
            {films.length > 0 ? (
              <>
                <h3 className="text-lg font-semibold text-white">
                  Найдено фильмов: {films.length}
                </h3>
                <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-4">
                  {films.map((film) => (
                    <FilmCard
                      key={film.kinopoiskId}
                      film={film}
                      onAdd={handleAddFilm}
                      showAddButton={!!onAddFilm}
                    />
                  ))}
                </div>
              </>
            ) : (
              <div className="text-center py-8">
                <p className="text-gray-400 text-lg">
                  Фильмы не найдены. Попробуйте другой запрос.
                </p>
              </div>
            )}
          </motion.div>
        )}
      </AnimatePresence>

      {/* Состояние загрузки */}
      <AnimatePresence>
        {isLoading && (
          <motion.div
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            exit={{ opacity: 0 }}
            className="flex items-center justify-center py-8"
          >
            <div className="flex items-center gap-3 text-gray-400">
              <Loader2 className="h-6 w-6 animate-spin" />
              <span>Поиск фильмов...</span>
            </div>
          </motion.div>
        )}
      </AnimatePresence>
    </div>
  );
}
